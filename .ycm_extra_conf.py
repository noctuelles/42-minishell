def Settings( **kwargs ):
  return {
    'flags': [ '-x', 'c', '-Wall', '-Werror', '-Wextra', '-I', 'libft/includes', '-I', 'includes', '-L .', '-l', 'ft' ],
  }
