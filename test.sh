#!/bin/sh
shuf /usr/share/dict/words | head -n $1 > /mnt/data/keys
sll/sll < /mnt/data/keys
dll/dll < /mnt/data/keys
bst/bst < /mnt/data/keys
avl/avl < /mnt/data/keys
ht/ht < /mnt/data/keys
