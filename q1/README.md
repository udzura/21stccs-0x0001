# Question 1

* Ruby製でSinatra を利用したアプリケーション `app.rb` があります。

```
$ ruby app.rb -- -q
```

* これで立ち上げたアプリケーションについて、以下のコマンドでアクセスすることができないと言う問題が起こっています。

```
$ curl localhost:4567
```

* 原因を探りましょう。

## Hint

* 以下のコマンドについて、 `strace` を経由して起動することでトレースしてみましょう。
    * `ruby app.rb`
    * `curl localhost:4567`
    * `ping localhost`

```
# e.g.
$ strace curl localhost:4567

# 絞り込みの例
$ strace -e connect curl localhost:4567
```
