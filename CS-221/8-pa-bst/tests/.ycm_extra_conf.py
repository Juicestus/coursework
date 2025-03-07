def Settings( **kwargs ):
	return {
		'flags': [
			'-x', 'c++',
			'-Wall', '-Wextra', '-Werror',
			'-Wno-unused-function',
			'-I', 'include',
			'-I', 'rtest/include',
			'-I', '../src',
		],
	}
