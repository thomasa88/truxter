#!/usr/bin/env python3
import sys

if len(sys.argv) != 2 or '-h' in sys.argv or '--help' in sys.argv:
    print('Usage: {} <input-file>'.format(sys.argv[0]))
    print()
    print('  Where input-file is a file containing the line-based table')
    print('  data copied from the data sheet.')
    print()
    print('  Output is printed to stdout.')
    sys.exit()

lines = open(sys.argv[1]).readlines()

prev = -4
next_reserved = 0
for line in lines:
    offset, name, type_, reset, *description, see_page = line.split()

    offset = int(offset, 16)

    if offset - prev > 4:
        padding_size = (offset - prev - 4)//4
        print('const pad_t reserved{}[{}];'.format(next_reserved, padding_size))
        next_reserved += 1

    prev = offset
    const = ''
    if type_ == 'RO':
        const = 'const '
    print('{}register_t {};'.format(const, name))
