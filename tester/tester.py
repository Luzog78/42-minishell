import os, traceback, re

bin_path = '/usr/bin/bash'
testing_path = './testing'
souffrance_path = './minishell.souffrance'

test_only: list[int] = []
print_failed_only = False

# Leave None to auto-detect a fixed prompt / heredoc prompt.
prompt_regex: str | None = None
heredoc_prompt_regex: str | None = None

# Set to False to print the detailed output of all tests.
# None to auto-detect.
print_repr: bool | None = None

# -------

C_RED = '\033[91m'
C_GREEN = '\033[92m'
C_YELLOW = '\033[93m'
C_BLUE = '\033[94m'
C_MAGENTA = '\033[95m'
C_CYAN = '\033[96m'
C_WHITE = '\033[97m'

C_BOLD = '\033[1m'
C_DIM = '\033[2m'
C_ITALIC = '\033[3m'
C_UNDERLINE = '\033[4m'

C_RESET = '\033[0m'


def print_error(message):
	print(f'{C_RED}{C_BOLD}Error:{C_RESET}{C_RED} {message}{C_RESET}')


def get_text(title, message, color=C_WHITE, indent=4) -> str:
	t = message.split('\n')
	s = f'{color}{C_BOLD}{title}:{C_RESET}\n'
	good_end = False
	if len(t) and t[-1] == '':
		del t[-1]
		good_end = True
	for i, line in enumerate(t):
		if i != 0:
			s += f'{C_DIM}${C_RESET}\n{color}'
		s += f'{" " * indent}{C_DIM}^{C_RESET}{color}{line}'
	if len(t) == 0:
		s += f'{" " * indent}'
	if good_end:
		s += f'{C_DIM}${C_RESET}'
	else:
		s += f'{C_DIM}%{C_RESET}'
	return s + C_RESET + '\n'


args: list[str] = os.sys.argv[1:]

if "-h" in args:
	p = lambda e, s, c_: print(f'{c_}{s}{C_RESET}', end='\n' if e else '')
	p(0, 'Usage:', C_CYAN + C_UNDERLINE + C_BOLD)
	p(0, f' {os.sys.argv[0]} ', C_CYAN + C_BOLD)
	p(1, f'[<flags...>] [<tests...>]', C_CYAN)
	p(1, '', '')
	p(1, 'Flags:', C_CYAN + C_UNDERLINE + C_BOLD)
	p(1, '    -h ........... : Display this help message', C_DIM)
	p(1, '    -b <path> .... : Path to the minishell binary', C_BLUE)
	p(1, '    -s <path> .... : Path to the minishell.souffrance file', C_BLUE)
	p(1, '    -t <path> .... : Path to the testing directory', C_BLUE)
	p(1, '    -o ........... : Print only failed tests', C_YELLOW)
	p(1, '    -f ........... : Print full detailed tests results', C_YELLOW)
	p(1, '    -ff .......... : Print sumed-up tests results', C_YELLOW)
	p(1, '    -p <regex> ... : Regex to detect the prompt', C_GREEN)
	p(1, '       none ...... :   (default) Auto-detect the prompt', C_GREEN)
	p(1, '    -hp <regex> .. : Regex to detect the heredoc prompt', C_GREEN)
	p(1, '       none ...... :   (default) Auto-detect the heredoc prompt', C_GREEN)
	exit(0)

while len(args):
	if args[0] == '-b':
		if len(args) < 2:
			print_error('No bin_path specified')
			exit(1)
		bin_path = args[1]
		args = args[2:]
	
	elif args[0] == '-s':
		if len(args) < 2:
			print_error('No souffrance_path specified')
			exit(1)
		souffrance_path = args[1]
		args = args[2:]
	
	elif args[0] == '-t':
		if len(args) < 2:
			print_error('No testing_path specified')
			exit(1)
		testing_path = args[1]
		args = args[2:]
	
	elif args[0] == '-o':
		print_failed_only = True
		args = args[1:]

	elif args[0] == '-f':
		print_repr = False
		args = args[1:]

	elif args[0] == '-ff':
		print_repr = True
		args = args[1:]
	
	elif args[0] == '-p':
		if len(args) < 2:
			print_error('No prompt_regex specified')
			exit(1)
		prompt_regex = args[1]
		args = args[2:]
	
	elif args[0] == '-hp':
		if len(args) < 2:
			print_error('No heredoc_prompt_regex specified')
			exit(1)
		heredoc_prompt_regex = args[1]
		args = args[2:]
	
	else:
		if not args[0].isdigit():
			print_error(f'Invalid argument: "{args[0]}"')
			exit(1)
		test_only.append(int(args[0]))
		args = args[1:]

if not bin_path:
	print_error('No bin_path specified')
	exit(1)

if not os.path.exists(bin_path):
	print_error(f'Could not find "{bin_path}"')
	exit(1)

if not souffrance_path:
	print_error('No souffrance_path specified')
	exit(1)

if not os.path.exists(souffrance_path):
	print_error(f'Could not find "{souffrance_path}"')
	exit(1)

if not testing_path:
	print_error('No testing_path specified')
	exit(1)

if not isinstance(test_only, list) and not isinstance(test_only, tuple):
	print_error('test_only must be a list')
	exit(1)

if any(not isinstance(i, int) for i in test_only) \
	or any(i < 0 for i in test_only):
	print_error('test_only must contain only positive integers')
	exit(1)

if prompt_regex is not None and not isinstance(prompt_regex, str):
	print_error('prompt_regex must be a string or None')
	exit(1)

if heredoc_prompt_regex is not None and not isinstance(heredoc_prompt_regex, str):
	print_error('heredoc_prompt_regex must be a string or None')
	exit(1)


if print_repr is None:
	print_repr = len(test_only) != 1


class Test:
	def __init__(self) -> None:
		self.input: str = ""

		self.expected: str = ""
		self.should_error: bool = False

		self.result_output: str | None = None
		self.result_error: str | None = None

		self.passed: bool | None = None
	
	def check(self) -> None:
		self.passed = True
		if self.should_error:
			if self.result_error == "":
				self.passed = False
				return
		else:
			if self.result_error != "":
				self.passed = False
				return
		
		if self.expected != self.result_output:
			self.passed = False

	def __str__(self) -> str:
		s = ''
		s += get_text('    Input', self.input, C_MAGENTA, 8)
		s += get_text('    Expected', self.expected, C_BLUE, 8)
		err = "Yes" if self.should_error else "No"
		s += f'    {C_YELLOW}Should error:{C_RESET} {C_YELLOW}{err}{C_RESET}\n'
		if self.passed is not None:
			s += '\n'
			s += get_text('    Standard Output', self.result_output, C_WHITE, 8)
			s += get_text('    Standard Error', self.result_error, C_RED, 8)
			s += '\n'
			if self.passed:
				s += f'    {C_GREEN}{C_BOLD}>>> [Passed] <<<{C_RESET}\n'
			else:
				s += f'    {C_RED}{C_BOLD}>>> [Failed] <<<{C_RESET}\n'
		return s[:-1]

	def __repr__(self) -> str:
		input = self.input.split('\n')
		expected = self.expected.split('\n')
		s = f'    {C_MAGENTA}{C_BOLD}Input:{C_RESET} {C_MAGENTA}{input}{C_RESET}\n' \
			+ f'    {C_BLUE}{C_BOLD}Expected:{C_RESET} {C_BLUE}{expected}{C_RESET}\n' \
			+ f'    {C_YELLOW}{C_BOLD}Should error:{C_RESET} {C_YELLOW}{self.should_error}{C_RESET}\n'
		if self.passed is not None:
			std_out = self.result_output.split('\n')
			std_err = self.result_error.split('\n')
			s += '\n'
			s += f'    {C_WHITE}{C_BOLD}Standard Output:{C_RESET} {C_WHITE}{std_out}{C_RESET}\n' \
				+ f'    {C_RED}{C_BOLD}Standard Error:{C_RESET} {C_RED}{std_err}{C_RESET}\n'
			s += '\n'
			if self.passed:
				s += f'    {C_GREEN}{C_BOLD}>>> [Passed] <<<{C_RESET}\n'
			else:
				s += f'    {C_RED}{C_BOLD}>>> [Failed] <<<{C_RESET}\n'
		return s[:-1]


class Stats:
	def __init__(self) -> None:
		self.total: list[int] = []
		self.passed: list[int] = []
		self.failed: list[int] = []
		self.crashed: list[int] = []
	
	def __str__(self) -> str:
		c = lambda s, c_: f'{c_}{s}{C_RESET}'
		ratio = float(len(self.passed) / float(len(self.total)) if len(self.total) \
			else 1.0 if len(self.passed) else 0.0) * 100.0
		ratio = f'{ratio:.2f}%'
		s = f'{c("Sum-Up :", C_CYAN + C_BOLD + C_UNDERLINE)}\n\n'

		s += f'    {c("Total ..... :", C_CYAN + C_BOLD)} ' \
			+ f'{c(len(self.total), C_CYAN)}'
		if len(self.crashed):
			s += f' {c("(", C_DIM)}{c(f"{len(self.crashed)} CRASHED", C_RED)}{c(")", C_DIM)}'
		s += '\n'

		s += f'    {c("Ratio ..... :", C_GREEN + C_BOLD)} ' \
			+ f'{c(len(self.passed), C_GREEN)}' \
			+ f'{c("/", C_DIM)}' \
			+ f'{c(len(self.failed), C_RED)} ' \
			+ f'{c("(", C_DIM)}{c(ratio, C_YELLOW)}{c(")", C_DIM)}\n'

		if len(self.failed) or len(self.crashed):
			s += '\n'
		if len(self.failed):
			s += f'    {c("Fails ..... :", C_RED + C_BOLD)} {c(self.failed, C_RED)}\n'
		if len(self.crashed):
			s += f'    {c("Crashes ... : ", C_RED + C_BOLD)} {c(self.crashed, C_RED)}\n'
		return s[:-1]


prompt = None
heredoc_prompt = None


def calibrate_prompts(output: str) -> None:
	global prompt, heredoc_prompt

	if prompt_regex is None:
		indexes = [m.start() for m in re.finditer('~CALIB~', output)]
		if len(indexes) != 3:
			print_error('Could not calibrate prompt')
			exit(1)

		prompt = ""
		while True:
			indexes[0] -= 1
			indexes[1] -= 1
			indexes[2] -= 1
			if not output[indexes[0]] == output[indexes[1]] == output[indexes[2]]:
				break
			prompt = output[indexes[0]] + prompt

		if prompt.startswith('\n'):
			prompt = prompt[1:]

		print(f'{C_DIM}Prompt calibrated to "{C_RESET}{prompt}{C_DIM}"...{C_RESET}')

	if heredoc_prompt_regex is None:
		indexes = [m.start() for m in re.finditer('~HCALIB~', output)]
		if len(indexes) != 3:
			print_error('Could not calibrate heredoc prompt')
			exit(1)

		heredoc_prompt = ""
		while True:
			indexes[0] -= 1
			indexes[1] -= 1
			indexes[2] -= 1
			if indexes[0] < 0 or indexes[1] < 0 or indexes[2] < 0 or not output[indexes[0]] == output[indexes[1]] == output[indexes[2]]:
				break
			heredoc_prompt = output[indexes[0]] + heredoc_prompt

		if heredoc_prompt.startswith('\n'):
			heredoc_prompt = heredoc_prompt[1:]

		print(f'{C_DIM}Heredoc prompt calibrated to "{C_RESET}{heredoc_prompt}{C_DIM}"...{C_RESET}')

	if prompt is not None or heredoc_prompt is not None:
		print()


def clean_output(output: str) -> str:
	def clean_base(output: str) -> str:
		if prompt_regex is not None:
			prompts = re.findall(prompt_regex, output)
			if not prompts or len(prompts) == 0:
				return output

			def p(prompt: str | tuple[str]):
				if isinstance(prompt, tuple):
					for pp in prompt:
						if pp:
							return pp
					return prompt[0]
				return prompt

			output = output[output.index(p(prompts[0])):]
			
			t = output.split('\n')
			t = [line for line in t if not any(line.startswith(p(prompt)) for prompt in prompts)]
			output = '\n'.join(t)

			return output

		if prompt is None or prompt == '':
			return output

		i = 0
		while i < len(output) and not output[i:].startswith(prompt):
			i += 1
		output = output[i:]
		
		t = output.split('\n')
		t = [line for line in t if not line.startswith(prompt)]
		output = '\n'.join(t)

		return output

	def clean_heredoc(output: str) -> str:
		if heredoc_prompt_regex is not None:
			prompts = re.findall(heredoc_prompt_regex, output)
			if not prompts or len(prompts) == 0:
				return output

			def p(prompt: str | tuple[str]):
				if isinstance(prompt, tuple):
					for pp in prompt:
						if pp:
							return pp
					return prompt[0]
				return prompt

			t = output.split('\n')
			t = [line for line in t if not any(line.startswith(p(prompt)) for prompt in prompts)]
			output = '\n'.join(t)

			return output

		if heredoc_prompt is None or heredoc_prompt == '':
			return output

		t = output.split('\n')
		t = [line for line in t if not line.startswith(heredoc_prompt)]
		output = '\n'.join(t)

		return output

	return clean_heredoc(clean_base(output))


souffrance = None

try:
	with open(souffrance_path, 'r') as f:
		souffrance = f.read().replace('%EOF', chr(4))
except:
	pass

if souffrance is None:
	print_error(f'Could not read "{souffrance_path}"')
	exit(1)

tests = [Test()]

i = 0
for line in souffrance.split('\n'):
	if line == '---':
		i += 1
		tests.append(Test())
	
	elif line.startswith('$ '):
		tests[i].input += line[2:] + '\n'
	
	elif line.startswith('@ '):
		tests[i].expected += line[2:] + '\n'
	
	elif line == '###': # line.startswith('! '):
		tests[i].should_error = True

del tests[-1]

tests.insert(0, Test())
tests[0].input = "~CALIB~\n~CALIB~\n~CALIB~\ncat << EOF\n~HCALIB~\n~HCALIB~\n~HCALIB~\n"

stats = Stats()


cwd = os.getcwd()
bin_path = bin_path.strip()
if not bin_path.startswith('/') and not bin_path.startswith('~'):
	bin_path = "../" + bin_path

os.system(f'rm -rf {testing_path}')
os.system(f'mkdir -p {testing_path}')
os.chdir(testing_path)

first = True
for i, test in enumerate(tests):
	if i and test_only and i not in test_only:
		continue

	if i:
		stats.total.append(i)

	try:
		os.system(f'rm -rf ./*')

		with open('.in.tmp', 'w') as f:
			f.write(test.input)

		os.system(f'{bin_path} < .in.tmp > .out.tmp 2> .err.tmp')

		with open('.out.tmp', 'r') as f:
			test.result_output = clean_output(f.read()) if i else f.read()
		
		with open('.err.tmp', 'r') as f:
			test.result_error = f.read()

		if i == 0:
			if prompt_regex is None or heredoc_prompt_regex is None:
				calibrate_prompts(test.result_output)
			continue

		test.check()

		if test.passed:
			stats.passed.append(i)
		else:
			stats.failed.append(i)

		if print_failed_only and test.passed and len(test_only) != 1:
			continue

		if not first:
			print('\n')
		print(f'{C_CYAN}{C_UNDERLINE}Test {C_BOLD}{i}:{C_RESET}')
		print(repr(test) if print_repr else test)
	except Exception as e:
		print(f'{C_RED}{C_BOLD}{C_UNDERLINE}Error while running test {i}:{C_RESET}' \
			+ f'{C_RESET} {C_RED}{C_BOLD}{e}{C_RESET}{C_RED}')
		traceback.print_exc()
		print(C_RESET)
		stats.crashed.append(i)
		if i == 0:
			first = False
			break
	first = False


os.chdir(cwd)
os.system(f'rm -rf {testing_path}')

if not first:
	print(f'\n================================\n')

print(stats)
