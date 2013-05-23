#/usr/bin/env python

def main():
  id_index = dict()
  index = 0
  for row in open('id_index.txt', 'r'):
    id_index[int(row)] = index
    index += 1
  for row in open('links.txt', 'r'):
    ids = row.strip().split(' ')
    string = str(id_index[int(ids[0])])
    for number in ids[1:]:
      if len(number) > 0 and int(number) in id_index.keys():
        string += ' ' + str(id_index[int(number)])
    print string


if __name__ == '__main__':
  main()
