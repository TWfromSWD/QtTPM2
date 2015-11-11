#include <QUdpSocket>
#include <QColor>

#include "tpm2_constants.h"
#include "tpm2_net.h"

Tpm2_net::Tpm2_net(QObject *parent) : QObject(parent)
{
  ledControllerSocket_ = new QUdpSocket( this );

  // Event zum erkennen, wenn Daten empfangen wurden
  connect( ledControllerSocket_, SIGNAL(readyRead()), this, SLOT(dataHasArrived()) );
}

Tpm2_net::~Tpm2_net()
{
  delete ledControllerSocket_;
}

bool Tpm2_net::open( const QString &ipAddress )
{
  if ( ipAddress.isEmpty() )
    return false;

  targetAddress_ = QHostAddress( ipAddress );

  ledControllerSocket_->connectToHost( targetAddress_, tpm2::TPM2_NET_PORT );

  return ledControllerSocket_->isOpen();
}

bool Tpm2_net::clearStripe( int ledCount )
{
  QByteArray allZeros;

  allZeros.fill( 0, ledCount * 3 );

  return sendDataPacket( *ledControllerSocket_, ledCount, allZeros );
}

bool Tpm2_net::sendDataPacket( QUdpSocket &socket, int ledCount, const QByteArray &ledData )
{
  if ( socket.isOpen() )
  {
    qDebug() << "Sending Data";

    QByteArray datagram;

    datagram += tpm2::TPM2_NET_BLOCK_START_BYTE;
    datagram += tpm2::TPM2_BLOCK_TYPE_DATA;

    int16_t frameSize = ledCount * 3;
    int8_t packetNumber = 1;
    int8_t packetCount = 1;

    datagram += (char)(frameSize >> 8);
    datagram += (char)(frameSize & 0xff);
    datagram += (char)packetNumber;
    datagram += (char)packetCount;

    datagram += ledData;

    datagram += tpm2::TPM2_BLOCK_END_BYTE;

    //qDebug() << datagram;

    socket.write(datagram);

    return true;
  }

  qDebug() << "Socket ist nicht geöffnet!";

  return false;
}

bool Tpm2_net::sendLedData( int ledCount, const QByteArray &ledData )
{
  if ( ledControllerSocket_ )
    return sendDataPacket( *ledControllerSocket_, ledCount, ledData );

  return false;
}

void Tpm2_net::dataHasArrived()
{
  qDebug() << ledControllerSocket_->readAll();
}



