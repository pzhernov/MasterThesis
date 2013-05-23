#/usr/bin/env python

def main():
  count = 0
  for row in open('links.txt', 'r'):
    ids = row.strip().split(' ')
    for number in ids[1:]:
      if len(number) > 0:
        count += 1
  print count

if __name__ == '__main__':
  main()
