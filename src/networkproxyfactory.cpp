#include "networkproxyfactory.h"

NetworkProxyFactory::NetworkProxyFactory()
    : m_proxy(QNetworkProxy::DefaultProxy)
{
}

NetworkProxyFactory::~NetworkProxyFactory()
{
}

QList<QNetworkProxy> NetworkProxyFactory::queryProxy(const QNetworkProxyQuery& query)
{
    QList<QNetworkProxy> proxyList;

    // if wildcard "*" specified completely disable the proxy
    if (m_whiteDomains.size() == 1 && m_whiteDomains.at(0) == "*") {
        proxyList.append(QNetworkProxy::NoProxy);
        return proxyList;
    }
    
    if (m_whiteDomains.contains(query.url().host(), Qt::CaseInsensitive))
        proxyList.append(QNetworkProxy::NoProxy);

    proxyList.append(m_proxy);

    return proxyList;
}

QStringList NetworkProxyFactory::whiteDomains() const
{
    return m_whiteDomains;
}

void NetworkProxyFactory::setWhiteDomains(const QStringList& whiteDomains)
{
    m_whiteDomains = whiteDomains;
}

void NetworkProxyFactory::addToWhiteDomains(const QString& domain)
{
    if (m_whiteDomains.contains(domain, Qt::CaseInsensitive)) {
        qDebug() << "Ignoring duplicate white domain";
        return;
    }

    m_whiteDomains.append(domain);
}

void NetworkProxyFactory::setProxy(QNetworkProxy::ProxyType proxyType, const QString& proxyHost, quint16 proxyPort)
{
    QNetworkProxy proxy(proxyType, proxyHost, proxyPort);
    m_proxy.setType(proxyType);
    m_proxy.setHostName(proxyHost);
    m_proxy.setPort(proxyPort);
}

void NetworkProxyFactory::setProxy(QNetworkProxy::ProxyType proxyType, const QString& proxyHost, quint16 proxyPort, const QString& proxyAuthUser, const QString& proxyAuthPass)
{
    setProxy(proxyType, proxyHost, proxyPort);
    m_proxy.setUser(proxyAuthUser);
    m_proxy.setPassword(proxyAuthPass);
}