# 概要

このリポジトリでは[GoogleAnalytics4のMeasurement Protocol](https://developers.google.com/analytics/devguides/collection/protocol/ga4)を利用するUnrealEngine用のGoogleMeasurementProtocolプラグインとそのサンプルプロジェクトを管理します。

# GoogleMeasurementProtocolプラグインについて

UnrealEngineのAnalyticsのRecordEventでMeasurement Protocolを使ってイベントを登録します。
UnrealEngine5.3向けにしていますが、特殊な処理はしていないためUnrealEngine5系なら問題なく動作するかと思います。

UnrealEngineでデスクトップアプリを作成する際に対応しているAnalyticsのプラットフォームとプラグインがほとんどなかったために作りました。Measurement Protocol利用のためにGoogleAnalyticsの豊富な機能は利用できませんが、カスタムイベントのデータを集計してGoogleのLoocker Studioなどを利用して自由に可視化ができます。

Editor Playの際はイベントは記録せずにログだけ出し、パッケージングではイベントを記録します。

# サンプルプロジェクトの使い方

* GoogleAnalytics4のプロパティを用意します。
* 用意したプロパティのデータストリームでAndroidストリームを追加します。
* AndroidストリームのFIREBASEアプリIDとMeasurement Protocol API secretを記録しておきます。
* このリポジトリをクローンします。
* Config/DefaultEngine.iniに以下の記述があるのを確認しておきます。
```ini
[Analytics]
ProviderModuleName=GMPAnalytics
```
* プロジェクトを起動します。
* [Editor] > [Project Settings] > [GMPAnalytics]の[Api Secret]、[Firebase App Id]の項目に記録しておいたMeasurement Protocol API secretとFIREBASEアプリIDを登録します。[GroupName]の項目の設定は任意です。
* パッケージングして、実行します。
* Record EventをするとGoogleAnalytics側のリアルタイムのレポートでイベントの登録が確認できます。

# ライセンス

[Apache License 2.0](LICENSE)