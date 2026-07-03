
{Server}
(Backend) SS1 <-> SS2 <-> (Front end NIC) {Client on this SS2}

AP SS
Sec SS
NW SS (Orchestror, CPUs for NW workloads)

struct payload
{
    int seq_num: 8;
    int cmd : 8;
    int act: 1;
    int respose: 1;
    int last_payload: 1;
    int *circular_queue;
}


bool ipc_send(ch, &tx_payload)

bool ipc_receive(ch, &rx_payload)


bool ipc_send_str(ch, &tx_payload)
bool ipc_receive_str(ch, &tx_payload)

