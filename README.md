## プロファイラの実行

```
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DPOLYNOMIAL_MULTIPLICATION_METHOD=NTT -DPROFILER=ON ..
make
./ThousandsBallot -P 12289 1024 1024 -N 12289 -S 10
gprof ./ThousandsBallot gmon.out > analysis.txt
```