#/usr/bin/env python

def main():
  count = 0
  for row in open('id_index.txt', 'r'):
    count += 1
  print count

if __name__ == '__main__':
  main()
