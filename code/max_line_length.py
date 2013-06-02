#/usr/bin/env python

### max_line_length.py ###

def main():
  max_line_length = 0
  for row in open('links.txt', 'r'):
    if len(row) > max_line_length:
      max_line_length = len(row)
  print max_line_length

if __name__ == '__main__':
  main()
