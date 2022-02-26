#!/bin/bash
set -e

for NUM in $(seq 1 2); do
	cmp --quiet <(./xor data/pad_$NUM.txt data/cypher_$NUM.txt) data/msg_$NUM.txt
	cmp --quiet <(./xor data/pad_$NUM.txt data/msg_$NUM.txt) data/cypher_$NUM.txt
done
