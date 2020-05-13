# PasswordCracker
Multi-threaded bruteforce 

![rotors](https://github.com/MaksymPylypenko/PasswordCracker/blob/master/brute-force/rotors.png)

## How it works?

All possible word/number combinations are represented using [Rotors]. You can imagine a word as:

`[0][0][0]`

By adding 1, we can get 

`[1][0][0]`, `[2][0][0]` ... `[9][0][0]`, `[0][1][0]`

If we repeat this proccess we would iterate all possible digits of length 3

`[0][0][0]` --> `[9][9][9]`

The value of a single rotor tells us a character index that will be used to build a word.
There are currently 3 charsets for numbers (d), lower-case letters (l) and upper-case letters (u).
Those charsets could also be mixed using a `mask`.

## Usage example

SHA-256 is the only available hash right now, but it shoudn't be difficult to use `cryptopp` library for other hashes as well.
For testing purposes, you may generate a SHA-256 hash using this [website](https://xorbin.com/tools/sha256-hash-calculator).
The number of threads should be close to the number of CPU cores (for better performance). Here are some test runs on Intel Core i7-2630QM 
``` 
Enter a SHA-256 hash (hex format): 2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824
Enter the mask (u/l/d): llllll
Enter the number of threads: 4
Thread (2) found a match = [hello]
Elapsed time: 3.54065 s
Thread (3) joined
Thread (1) joined
Thread (0) joined
```

Just for comparision, this is the same hash using only 1 thread.
```
Enter a SHA-256 hash (hex format): 2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824
Enter the mask (u/l/d): llllll
Enter the number of threads: 1
Thread (0) found a match = [hello]
Elapsed time: 25.9151 s
```

Or treads > cpu cores
```
Enter a SHA-256 hash (hex format): 2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824
Enter the mask (u/l/d): llllll
Enter the number of threads: 10
Thread (5) found a match = [hello]
Elapsed time: 5.61054 s
Thread (9) joined
Thread (1) joined
Thread (0) joined
Thread (6) joined
Thread (8) joined
Thread (3) joined
Thread (2) joined
Thread (4) joined
Thread (7) joined

```

Suprisingly, using 20 threads is kinda better. However, this makes the OS unusable during the bruteforce.
```
Enter a SHA-256 hash (hex format): 2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824
Enter the mask (u/l/d): llllll
Enter the number of threads: 20
Thread (11) found a match = [hello]
Elapsed time: 2.16732 s
Thread (6) joined
Thread (14) joined
Thread (1) joined
Thread (9) joined
Thread (4) joined
Thread (2) joined
Thread (7) joined
Thread (3) joined
Thread (16) joined
Thread (15) joined
Thread (5) joined
Thread (10) joined
Thread (8) joined
Thread (0) joined
Thread (12) joined
Thread (18) joined
Thread (19) joined
Thread (17) joined
Thread (13) joined
```

## External Libraries
* [CryptoPP](https://github.com/weidai11/cryptopp) - cryptographic algorithms and schemes written by Wei Dai.
* [GoogleTest](https://github.com/google/googletest) - testing and mocking Framework


## PC specs 
The program was successfully tested using:
* Processor: Intel(R) Core(TM) i7-2630QM CPU @ 2.00GHz
  * Cores: 4
  * Threads: 8
* RAM: 8.00GB
* OS: 64-bit Windows 10
* IDE: Visual Studio 2019 16.4
