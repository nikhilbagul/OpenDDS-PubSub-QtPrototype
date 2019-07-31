/*
 *
 *
 * Distributed under the OpenDDS License.
 * See: http://www.opendds.org/license.html
 */

#include "DataReaderListenerImpl.h"
#include "Boilerplate.h"
#include <iostream>

using namespace boilerplate;

DataReaderListenerImpl::DataReaderListenerImpl() : sample_count(0)
{
}

void DataReaderListenerImpl::on_data_available(DDS::DataReader_ptr reader)
{
    std::cout << "Data sample available !" << endl;

    // Safely downcast data reader to type-specific data reader
    Messenger::MessageDataReader_var reader_i = narrow(reader);

    Messenger::Message msg;
    DDS::SampleInfo info;

    // Remove (take) the next sample from the data reader
    //DDS::ReturnCode_t error = reader_i->take_next_sample(msg, info);
    DDS::ReturnCode_t error = reader_i->read_next_sample(msg, info);


    std::cout << info.source_timestamp.sec << endl;
    std::cout << info.sample_state << endl;

    if (info.sample_state == DDS::READ_SAMPLE_STATE)
    {
        std::cout << "Message read!";
    }

    // Make sure take was successful
    if (error == DDS::RETCODE_OK) {
        // Make sure this is not a sample dispose message
        if (info.valid_data) {
            ++sample_count;
            std::cout << "FIXED_ID : " << msg.fixed_id.in() << std::endl
                      << "Type     : " << msg.type.in()   << std::endl
                      << "Value    : " << msg.value.in()    << std::endl;

        }
    } else {
        ACE_ERROR((LM_ERROR,
                   ACE_TEXT("ERROR: %N:%l: on_data_available() -")
                   ACE_TEXT(" take_next_sample failed!\n")));
    }
}
