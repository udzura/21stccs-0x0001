# Question 3

* 以下の Apache モジュールをコンパイルします。

```
$ make
```

* 以下の手順でインストールし、Apacheにロードします。

```
$ sudo make install
$ sudo cp twentyfirst.load /etc/apache2/mods-available/
$ sudo a2enmod twentyfirst
$ sudo systemctl restart apache2
```

* このApacheのパス `/21stccs` に負荷をかけてそのワークロードの性質を検査してください。
* 負荷はシンプルに Apache Bench で構いません。また、今回は手抜きで (^^:) 負荷をかける対象のホストと同じホストでベンチマーカを走らせて構いません。

```
$ ab -n 300 localhost/21stccs                          
This is ApacheBench, Version 2.3 <$Revision: 1879490 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/        
                                                                             
Benchmarking localhost (be patient)
Completed 100 requests
...
```

## Hint

* 計測の対象は以下の要領で特定し、 `perf` コマンドのパラメータに追加します。

```
$ ps auxf
...
root       31712  0.0  0.0   6632  4496 ?        Ss   08:37   0:00 /usr/sbin/apache2 -k start
www-data   31713  0.0  0.0 1997940 4332 ?        Sl   08:37   0:00  \_ /usr/sbin/apache2 -k start
www-data   31714  0.0  0.0 1997940 4332 ?        Sl   08:37   0:00  \_ /usr/sbin/apache2 -k start

$ sudo perf record -g -p 31712,31713,31714
[ perf record: Woken up 5 times to write data ]
[ perf record: Captured and wrote 1.113 MB perf.data (12454 samples) ]
```

* 計測結果は `perf record` で表示します。

```
$ sudo perf report -g --stdio
```
