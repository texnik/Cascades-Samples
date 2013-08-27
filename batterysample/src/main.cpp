/* Copyright (c) 2012, 2013  BlackBerry Limited.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/device/BatteryInfo>

#include <QtCore/QLocale>
#include <QtCore/QTranslator>

using namespace bb::cascades;
using namespace bb::device;

/**
 * This sample application shows some basic
 * usage of the BatteryInfo API, such as charging level and charging state.
 */
Q_DECL_EXPORT int main(int argc, char **argv)
{
    qmlRegisterUncreatableType<bb::device::BatteryChargingState>("bb.device", 1, 0, "BatteryChargingState", "");

    Application app(argc, argv);

    QTranslator translator;
    const QString locale_string = QLocale().name();
    const QString filename = QString("batterysample_%1").arg(locale_string);
    if (translator.load(filename, "app/native/qm")) {
        app.installTranslator(&translator);
    }

//! [0]
    // Create the battery info object
    BatteryInfo batteryInfo;

    // Load the UI description from main.qml
    QmlDocument *qml = QmlDocument::create("asset:///main.qml");

    // Make the BatteryInfo object available to the UI as context property
    qml->setContextProperty("_battery", &batteryInfo);
//! [0]

    // Create the application scene
    AbstractPane *appPage = qml->createRootObject<AbstractPane>();
    Application::instance()->setScene(appPage);


    return Application::exec();
}
