#ifndef TPM2_NET_H
#define TPM2_NET_H

#include <QObject>
#include <QUdpSocket>

class Tpm2_net : public QObject
{
  Q_OBJECT

  public:           
    explicit Tpm2_net(QObject *parent = 0);
    ~Tpm2_net();

    //! Öffnet die Verbindung
    bool open(const QString &ipAddress = "");

    //! Setzt die angegebene Anzahl von LEDs auf 0
    bool clearStripe(int ledCount);
    //! Schickt die RGB LED Daten
    bool sendLedData(int ledCount, const QByteArray &ledData);

  private:
    QUdpSocket *ledControllerSocket_;
    QHostAddress targetAddress_;

    bool sendDataPacket(QUdpSocket &socket, int ledCount, const QByteArray &ledData);

  signals:

  public slots:
    void dataHasArrived();
};

#endif // TPM2_NET_H
