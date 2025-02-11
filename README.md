# Bang-Lish

Linux shell in C

### PROJECT IS UNDER DEVLOPMENT

## Build and test this project

Install build dependencies

```sh
sudo apt install gcc cmake make # On Ubuntu
```

Clone this repo and open this project

```sh
git clone https://github.com/abrarshakhi/bang-lish.git
cd bang-lish
```

Create a build dir if not exists and open it

```sh
mkdir build
```

then do

```sh
cmake -B build
```

if succesfull the do

```sh
make -C build
```

there should be a executable file named `banglish` onn build dir, Run it

```sh
./build/banglish
```

