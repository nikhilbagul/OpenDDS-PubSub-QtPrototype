#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "DataReaderListenerImpl.h"
#include "Boilerplate.h"

#include <dds/DCPS/Service_Participant.h>
#include <model/Sync.h>
#include "dds/DCPS/StaticIncludes.h"

using namespace boilerplate;
int initializeDDSSubscriber(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    initializeDDSSubscriber(argc, argv);

    return app.exec();
}

int initializeDDSSubscriber(int argc, char *argv[])
{
    // Initialize DomainParticipantFactory, handling command line args
    DDS::DomainParticipantFactory_var dpf =
            TheParticipantFactoryWithArgs(argc, argv);

    // Create domain participant
    DDS::DomainParticipant_var participant = createParticipant(dpf);

    // Register type support and create topic
    DDS::Topic_var topic = createTopic(participant);

    // Create subscriber
    DDS::Subscriber_var subscriber = createSubscriber(participant);

    // Create Listener
    DataReaderListenerImpl* listener_impl = new DataReaderListenerImpl;
    DDS::DataReaderListener_var listener(listener_impl);

    // Create DataReader with the listener attached
    DDS::DataReader_var reader = createDataReader(subscriber, topic, listener);

    // Set Data Reader QOS policy to prevent redundancy due to delay
    DDS::DataReaderQos policy;
    policy.reader_data_lifecycle.autopurge_nowriter_samples_delay.sec = 0.01;
    policy.reader_data_lifecycle.autopurge_disposed_samples_delay.sec = 0.01;
    reader->set_qos(policy);

    {
        // Block until reader has associated with a writer
        // but is no longer associated with any writer
        OpenDDS::Model::ReaderSync rs(reader);
    }

    // Output the sample count
    std::cout << "Subscriber received " << listener_impl->sample_count
              << " samples" << std::endl;

    // Clean-up!
    cleanup(participant, dpf);

    return 0;
}

