# Distributed PasswordCracker
Multi-threaded bruteforce 

## How it works?
The idea is to divide all possible password combinations into managable chunks.

``` 
Enter a SHA-256 hash (hex format): 2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824
Enter the mask (u/l/d): llllll
Enter the number of threads: 4
[a][a][a][a][a][a] --> [z][z][z][z][m][g]
[a][a][a][a][n][g] --> [z][z][z][z][z][m]
[a][a][a][a][a][n] --> [z][z][z][z][m][t]
[a][a][a][a][n][t] --> [z][z][z][z][z][z]
Thread (3) found a match = [hello]
Thread (2) joined
Thread (0) joined
Thread (1) joined
Elapsed time: 4.2272 s
```

Just for comparision, this is the same hash using only 1 thread.
```
Enter a SHA-256 hash (hex format): 2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824
Enter the mask (u/l/d): llllll
Enter the number of threads: 1
[a][a][a][a][a][a] --> [z][z][z][z][z][z]
Thread (0) found a match = [hello]
Elapsed time: 21.9668 s
```

## Features (to-do)
* [x] Ability to bruteforce all possible character combinations
* [x] Ability to apply masks (e.g combine numbers & letters in a cpesific order)
* [x] Ability to bruteforce a certain region in P (plain-text space).
* [x] Ability to divide P by N equal regions. 
* [ ] Multi-threaded bruteforce
* [ ] Theead Pool
* [ ] Compare performance
