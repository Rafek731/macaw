from argparse import ArgumentParser

parser = ArgumentParser()
parser.add_argument('literowosc', type=int)
args = parser.parse_args()
n = args.literowosc
i =0 
with open('slowa.txt', 'r') as slowa, open(f'{n}literowe.txt', 'w') as out:

    line = slowa.readline()
    while line:
        i+=1
        if i % 10000 == 0:
            print(i)
        if(len(line) == n + 1):
            out.write(line)
        line = slowa.readline()
    
