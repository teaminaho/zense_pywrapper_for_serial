# 概要
センサ番号取得するためにzenseを起動するだけのモジュール

# インストール
```
python setup.py install --user
```

# 使用例
```
In [1]: from zense_pywrapper_for_serial import PyPicoZenseModuleForSerial

In [2]: zns = PyPicoZenseModuleForSerial(0)
Detected 2 devices.
sensor_idx_:0
SERIAL : PD71A1DGD6260045P

In [3]: print(zns.getSerialNumber())
PD71A1DGD6260045P

In [4]: delete zns
    delete zns

In [5]: del zns
Segmentation fault (コアダンプ)
```

デストラクタで必ずセグフォするが、使用上は問題ない


# 注意点
コード内でopencvは使用していないが、setup.pyのopencv参照の記述を削除するとエラーを吐く(センサAPIの方で陰的に参照している?)