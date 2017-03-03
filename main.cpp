#include <QtCore/QUrl>
#include <QtCore/QCommandLineOption>
#include <QtCore/QCommandLineParser>
#include <QDebug>
#include <QtWebEngineWidgets>
#include "jxbridge.h"

QWebEngineView *view;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Parse command line input URL
    QCommandLineParser parser;
    QCoreApplication::setApplicationVersion("0.0.1");
    parser.setApplicationDescription(QGuiApplication::applicationDisplayName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("url", "The URL to open.");
    QStringList arguments = app.arguments();
    parser.process(arguments);
    const QString initialUrl = parser.positionalArguments().isEmpty() ? QStringLiteral("http://www.baidu.com") : parser.positionalArguments().first();
    // end

    // Set window style
    view = new QWebEngineView();
    view->setWindowFlags(Qt::FramelessWindowHint);
    view->setAttribute(Qt::WA_TranslucentBackground);
    view->setFixedSize(1024, 768);
    // end

    // JS invoke Qt prepare
    QWebChannel *channel = new QWebChannel(view);
    channel->registerObject("bridge", (QObject*)JXBridge::instance());
    view->page()->setWebChannel(channel);
    // end

    view->load(QUrl(initialUrl));
    view->show();

    // Qt invoke js
    //    view->page()->runJavaScript(QObject::tr("alert('Qt invoke js')"));

    QObject::connect(view, &QWebEngineView::loadFinished, []() {
        view->page()->runJavaScript("showAlert()");
    });

    return app.exec();
}
