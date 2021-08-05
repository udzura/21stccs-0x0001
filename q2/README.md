# Question 2

* 以下の2つのスクリプトを実行してみましょう。どちらも、同じように実行時間がかかると思います。

```
$ ruby load1.rb
....
$ ruby load2.rb
....
```

* この2つのスクリプトの中身を見ずに、それぞれの処理のワークロードの性質（中でやっていること）は何か、ボトルネックが何であるか当ててみてください。

## Hint

* `strace` コマンドには `-c` オプションがあります。その出力を基に分析することが可能かもしれません。

```
$ strace -c ruby load1.rb
# ...
```

* また、 `-c` と `-cw` で結果が変わるはずです。それぞれのオプションの違いを認識し、比較しましょう。

```
$ strace -cw ruby load1.rb
# ...
```