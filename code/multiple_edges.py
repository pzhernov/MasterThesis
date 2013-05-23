#/usr/bin/env python

def main():
  for row in open('links.txt', 'r'):
    ids = row.strip().split(' ')
    for number in ids[1:]:
      if len(number) > 0:
        print ids[0] + ' ' + number

if __name__ == '__main__':
  main()
