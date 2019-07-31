# Compaction-Algorithm

说明：将 cpp 文件放入 testdata 文件夹后编译，命令行运行 "*filename*.exe 16" 即可运行测试。

## Huffman Code

考场代码：哈夫曼编码（写的很丑，因为 priority_queue 记反了调了好久）

### Algorithm

Too classic, skipped.

唯一要说的一点就是可以通过传词频，在压缩和解压同时构造字典（Huffman Tree）来优化压缩率。

### Result

Huffman：704 / 1600：没有使用分隔符（可能导致文件中部出现EOF）（懒得改成处理EOF的方案，先这样吧）

```
Test #1: Your compress Ratio 157.894737
Test #2: Your compress Ratio 42.324457
Test #3: Your compress Ratio 43.048183
Test #4: Your compress Ratio 42.274135
Test #5: Your compress Ratio 42.495368
Test #6: Your compress Ratio 42.628533
Test #7: Your compress Ratio 56.830408
Test #8: Your compress Ratio 58.141503
Test #9: Your compress Ratio 58.768057
Test #10: Your compress Ratio 56.646074
Test #11: Your compress Ratio 56.591231
Test #12: Your compress Ratio 61.679972
Test #13: Your compress Ratio 56.964662
Test #14: Your compress Ratio 60.510227
Test #15: Your compress Ratio 68.804813
Test #16: Your compress Ratio 47.784460
```

## LZ77

### Algorithm

压缩过程：对于待编码区的内容，在窗口区寻找最长匹配，编码为 (offset, length) 二元组；如果不存在匹配，则编码为 (0, ch) 二元组。

解压缩过程：和压缩过程完全相同，利用编码即可在窗口区寻找到真实字符并还原。

### Result

LZ77-1：没有使用分割符（可能会导致文件中部出现EOF）。若需要修正该问题，则只需要将 IS_DIV 设置为 1 即可，但设置后压缩率没有 LZ77-2 优秀。

```
Test #1: Your compress Ratio 89.473684
Test #2: Your compress Ratio 62.692137
Test #3: Your compress Ratio 72.714349
Test #4: Your compress Ratio 81.756015
Test #5: Your compress Ratio 78.999481
Test #6: Your compress Ratio 54.283072
Test #7: Your compress Ratio 55.409444
Test #8: Your compress Ratio 56.104717
Test #9: Your compress Ratio 56.087876
Test #10: Your compress Ratio 55.704464
Test #11: Your compress Ratio 55.634354
Test #12: Your compress Ratio 58.677543
Test #13: Your compress Ratio 56.097998
Test #14: Your compress Ratio 56.000453
Test #15: Your compress Ratio 103.276640
Test #16: Your compress Ratio 45.492175
```

LZ77-2：没有使用分隔符，但是对编码进行了特殊处理使得不会出现 EOF 情况。

```
Test #1: Your compress Ratio 100.000000
Test #2: Your compress Ratio 70.762278
Test #3: Your compress Ratio 80.954865
Test #4: Your compress Ratio 91.886684
Test #5: Your compress Ratio 88.471800
Test #6: Your compress Ratio 60.559726
Test #7: Your compress Ratio 61.927403
Test #8: Your compress Ratio 62.734146
Test #9: Your compress Ratio 62.626368
Test #10: Your compress Ratio 62.221004
Test #11: Your compress Ratio 62.182188
Test #12: Your compress Ratio 65.515446
Test #13: Your compress Ratio 62.648363
Test #14: Your compress Ratio 62.676428
Test #15: Your compress Ratio 115.577924
Test #16: Your compress Ratio 51.708520
```

## LZSS

### Algorithm

在 LZ77 的基础上，加上了最小长度限制。

### Result

LZSS-1：没有使用分割符（可能会导致文件中部出现EOF）。若需要修正该问题，则只需要将 IS_DIV 设置为 1 即可，但设置后压缩率没有 LZSS-2 优秀。

```
Test #1: Your compress Ratio 105.263158
Test #2: Your compress Ratio 63.714574
Test #3: Your compress Ratio 70.595665
Test #4: Your compress Ratio 77.200914
Test #5: Your compress Ratio 74.160676
Test #6: Your compress Ratio 54.474613
Test #7: Your compress Ratio 59.892409
Test #8: Your compress Ratio 59.402505
Test #9: Your compress Ratio 59.987984
Test #10: Your compress Ratio 59.994022
Test #11: Your compress Ratio 60.217626
Test #12: Your compress Ratio 63.201435
Test #13: Your compress Ratio 60.518655
Test #14: Your compress Ratio 59.864895
Test #15: Your compress Ratio 52.016661
Test #16: Your compress Ratio 37.524533
```

LZSS-2：没有使用分隔符，但是对编码进行了特殊处理使得不会出现 EOF 情况。

```
Test #1: Your compress Ratio 115.789474
Test #2: Your compress Ratio 71.904776
Test #3: Your compress Ratio 79.648267
Test #4: Your compress Ratio 87.078702
Test #5: Your compress Ratio 83.650041
Test #6: Your compress Ratio 61.499423
Test #7: Your compress Ratio 67.149378
Test #8: Your compress Ratio 66.607425
Test #9: Your compress Ratio 67.247460
Test #10: Your compress Ratio 67.260363
Test #11: Your compress Ratio 67.508521
Test #12: Your compress Ratio 70.831887
Test #13: Your compress Ratio 67.848345
Test #14: Your compress Ratio 67.103178
Test #15: Your compress Ratio 58.245979
Test #16: Your compress Ratio 42.166977
```

可以发现，两份 LZSS 代码在 #15 测试点上都表现得比 LZ77 优秀很多。

## LZ78

### Algorithm

利用字典树 Trie 建树的原理，每次在树上往下走，以 (id, ch) 二元组表示在编号为 id 的点的 ch 这条路径的终点新建一个儿子。

解压也同样建一棵 Trie 树即可。

### Result

LZ78：简单实现

```
Test #1: Your compress Ratio 131.578947
Test #2: Your compress Ratio 55.824144
Test #3: Your compress Ratio 56.365766
Test #4: Your compress Ratio 59.342348
Test #5: Your compress Ratio 56.667161
Test #6: Your compress Ratio 47.418697
Test #7: Your compress Ratio 62.783242
Test #8: Your compress Ratio 64.722974
Test #9: Your compress Ratio 65.957002
Test #10: Your compress Ratio 62.372957
Test #11: Your compress Ratio 62.315558
Test #12: Your compress Ratio 68.598866
Test #13: Your compress Ratio 62.561025
Test #14: Your compress Ratio 68.276851
Test #15: Your compress Ratio 65.544371
Test #16: Your compress Ratio 44.737306
```

