#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <Boilerplate.h>

#include "dds/DCPS/StaticIncludes.h"
#include <dds/DCPS/Service_Participant.h>
#include <model/Sync.h>
#include <stdexcept>
#include <thread>         // std::thread, std::this_thread::sleep_for

int initializeDDSPublisher(int argc, char *argv[]);
int sendMessage(int argc, char *argv[], Messenger::MessageDataWriter_var& msg_writer_ref);
using namespace boilerplate;

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    initializeDDSPublisher(argc, argv);
    //std::thread th(initializeDDSPublisher,argc, argv);

    return app.exec();
}


int initializeDDSPublisher(int argc, char *argv[])
{
    // Initialize DomainParticipantFactory, handling command line args
    DDS::DomainParticipantFactory_var dpf =
            TheParticipantFactoryWithArgs(argc, argv);

    // Create domain participant
    DDS::DomainParticipant_var participant = createParticipant(dpf);

    // Register type support and create topic
    DDS::Topic_var topic = createTopic(participant);

    // Create publisher
    DDS::Publisher_var publisher = createPublisher(participant);

    // Create data writer for the topic
    DDS::DataWriter_var writer = createDataWriter(publisher, topic);

    // Set Data writer QOS policy to prevent redundancy due to delay
    DDS::DataWriterQos policy;
    policy.writer_data_lifecycle.autodispose_unregistered_instances = true;
    writer->set_qos(policy);

    // Safely downcast data writer to type-specific data writer
    Messenger::MessageDataWriter_var msg_writer = narrow(writer);


    // Block until Subscriber is available
    OpenDDS::Model::WriterSync ws(writer);

    bool isPublisherRunning = true;
    char input;
    while (isPublisherRunning)
    {
        std::cout << " Do you want to publish the next message (Y or N) : ";
        std::cin >> input;

        //input = 'y';
        if (input == 'Y' || input == 'y')
        {
            sendMessage(argc, argv, msg_writer);
            input = 'n';
            isPublisherRunning = true;
        }
        else
        {
            isPublisherRunning = false;
        }
    }

    // Clean-up!
    cleanup(participant, dpf);

    return 0;
}

int sendMessage(int argc, char *argv[], Messenger::MessageDataWriter_var& msg_writer_ref)
{
    // Initialize samples
    Messenger::Message message;
    message.fixed_id = "TIRE_PRESSURE_FL";
    message.type = "number";
    message.value = "39";

    // Publish the message
    DDS::ReturnCode_t error = msg_writer_ref->write(message,
                                                    DDS::HANDLE_NIL);
    if (error != DDS::RETCODE_OK) {
        ACE_ERROR((LM_ERROR,
                   ACE_TEXT("ERROR: %N:%l: main() -")
                   ACE_TEXT(" write returned %d!\n"), error));
    }

    // End of WriterSync scope - block until messages acknowledged
}

