#ifndef NETWORKPROXYFACTORY_H
#define NETWORKPROXYFACTORY_H

#include <QStringList>
#include <QUrl>
#include <QNetworkProxyFactory>

class NetworkProxyFactory : public QNetworkProxyFactory	
{
    Q_PROPERTY(QStringList whiteDomains READ whiteDomains WRITE setWhiteDomains)

public:
    NetworkProxyFactory();
    ~NetworkProxyFactory();
    QList<QNetworkProxy> queryProxy(const QNetworkProxyQuery &query = QNetworkProxyQuery());
    QStringList whiteDomains() const;
    void setWhiteDomains(const QStringList& whiteDomains);
    void addToWhiteDomains(const QString& domain);
    void setProxy(QNetworkProxy::ProxyType proxyType, const QString& proxyHost, quint16 proxyPort);
    void setProxy(QNetworkProxy::ProxyType proxyType, const QString& proxyHost, quint16 proxyPort, const QString& proxyAuthUser, const QString& proxyAuthPass);

private:
    QStringList	m_whiteDomains;
    QNetworkProxy m_proxy;
};

#endif /* NETWORKPROXYFACTORY_H */