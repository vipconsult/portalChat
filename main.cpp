#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QItemSelectionModel>
#include <QtQml>
#include <QQuickView>
#include <QTreeView>
#include <Contacts.cpp>


//TODO features
//    show user presence from facebook
//    file uploads ?

//  when chating with a user show tickboxes which technicians to notify for new messages.
//  support hashtags - to force a notify even when a technician is not selected to be notified
//  think how to design it so we can create temp groups

void addProfiles(Contacts *model){



    QNetworkAccessManager *manager = new QNetworkAccessManager();

    QNetworkRequest request(QUrl("https://dev.portal.vip-consult.co.uk/webhook/messenger/v1/profile"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QString("application/json"));

    manager->get(request);
    QObject::connect(manager, &QNetworkAccessManager::finished,model,&Contacts::setData);

}

int main(int argc, char *argv[])
{

    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);





//    qmlRegisterType<Contacts>("vipconsult.portal.chat", 1, 0, "Contacts");

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;

    Contacts ContactsModel;

    addProfiles(&ContactsModel);

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    QQmlContext *ctxt = view.rootContext();
    ctxt->setContextProperty("ContactsModel", &ContactsModel);

    view.setSource(QUrl("qrc:main.qml"));
    view.show();
    view.setWidth(600);
    view.setHeight(400);
    return app.exec();
}



