# Question 3

* 今度は以下のスクリプトを `strace -c [-w]` で分析してみましょう。

```
$ strace -cw ruby load3.rb
```

* 確かに実行時間がかかっているにもかかわらず、システムコールの統計からはワークロードが想像できません。何をしているか判別できるようにするにはどうすればいいでしょうか？

```
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
 99.11    7.538728     3769363         2         2 ppoll
  0.17    0.013108          36       361       204 openat
  0.14    0.010571          33       315         3 lstat
  0.10    0.007707          34       226           read
  0.07    0.005174          32       161           close
  0.07    0.005003          31       160           fstat
  0.06    0.004400          34       127        14 stat
  0.04    0.002939          31        94        91 ioctl
  0.04    0.002927          48        60           mmap
  0.02    0.001724          31        54           fcntl
  0.02    0.001709          35        48           mprotect
  0.02    0.001476          33        44           getegid
  0.02    0.001450          29        50           lseek
  0.02    0.001450          33        43           getgid
  0.02    0.001428          32        44           geteuid
  0.02    0.001391          32        43           getuid
  0.02    0.001155          41        28           brk
  0.01    0.000605          31        19           rt_sigaction
  0.01    0.000439          43        10           getdents64
  0.01    0.000421          46         9           getpid
  0.00    0.000328         163         2           vfork
  0.00    0.000262         262         1           execve
  0.00    0.000226          56         4           timer_settime
...
```

## Hint

* strace はデフォルトでは、当該プログラムからさらにforkしたプログラムをトレースしません。
* 以下の例では、外部の `uname` コマンドが発行する `uname(2)` をトレースできません。

```
$ strace -e uname ruby -e 'system "uname -a"'
Linux ubuntu-groovy 5.8.0-63-generic #71-Ubuntu SMP Tue Jul 13 15:59:12 UTC 2021 x86_64 x86_64 x86_64 GNU/Linux
--- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=38109, si_uid=1000, si_status=0, si_utime=0, si_stime=0} ---
+++ exited with 0 +++
```

* プログラムの中でさらにforkする場合のためのオプションが存在します。

```
$ strace ?? -e uname ruby -e 'system "uname -a"'
strace: Process 38153 attached
[pid 38153] uname({sysname="Linux", nodename="ubuntu-groovy", ...}) = 0
[pid 38153] uname({sysname="Linux", nodename="ubuntu-groovy", ...}) = 0
[pid 38153] uname({sysname="Linux", nodename="ubuntu-groovy", ...}) = 0
Linux ubuntu-groovy 5.8.0-63-generic #71-Ubuntu SMP Tue Jul 13 15:59:12 UTC 2021 x86_64 x86_64 x86_64 GNU/Linux
[pid 38153] +++ exited with 0 +++
--- SIGCHLD {si_signo=SIGCHLD, si_code=CLD_EXITED, si_pid=38153, si_uid=1000, si_status=0, si_utime=0, si_stime=0} ---
+++ exited with 0 +++
```
