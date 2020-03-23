# 概要
センサ番号取得するためにzenseを起動するだけのモジュール

# インストール
1. 依存パッケージをインストールする(userのオプションはあってもなくてもインストールできる状態であればOK)
```
pip install --user -r requirements.txt
```
2. 下のインストール説明に沿ってPicoZenseSDKをインストールし、下のコマンドを入力する(docker-composeによるインストールの場合は基本この手順は不要)
https://github.com/teaminaho/aspara_robo/blob/master/cv_setup.md
```
sudo ./install.sh
```

3. zense_pywrapper_for_serialパッケージをインストールする(userオプションについては同様) 
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
```

# 注意点
 - コード内でopencvは使用していないが、setup.pyのopencv参照の記述を削除するとエラーを吐く(センサAPIの方で陰的に参照している?)
 - 以前のコードではデストラクタ呼び出し時に必ずセグフォが発生していたが、PsShutdown()の前にPsCloseDevice()を呼ぶことで解消された(ただ、最新のコードではそもそもPsShutdown()を使っていない)