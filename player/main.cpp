#include <QUdpSocket>
#include <QThread>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Player{
    string teamName;
    string playMode;
    string number;
    string side;
    string commandToSend;
    string msg;
};

vector<string> split(string const & str, char separator){
    std::vector<string> words;

    // create a stream from the string
    stringstream s(str);
    string s2;
    while (getline(s, s2, separator))
    {
        words.push_back(s2); // store the string in s2
    }
    return words;
}

Player before_kick_off(Player const & player){
    Player p{player};
    if(p.side == "r"){ // right side
        if(p.number == "2") p.commandToSend = "(move 30 -25)";
        if(p.number == "3") p.commandToSend = "(move 30 25)";
    }
    else { // left side
        if(p.number == "2") p.commandToSend = "(move -30 -25)";
        if(p.number == "3") p.commandToSend = "(move -30 25)";
    }

    return p;
}

Player generateCommand(Player const & player){
    Player p{player};
    p.commandToSend.clear();

    // BEFORE KICK OFF
    if(p.playMode=="before_kick_off"){
        p = before_kick_off(p);
    }
    // ... more functions

    return p;
}

/**
 * @brief parseInitMsg Function to run when (init ...) msg is received
 * @param msg the full message
 * @param player
 * @return player with updated data.
 */
Player parseInitMsg(Player const & player){
    Player p{player};
    int pos = p.msg.find("(init");
    if(pos != -1){
        int posf = p.msg.find(")", pos);
        string initmsg = p.msg.substr(pos+1, posf-pos-1);
        cout << initmsg << "\n";
        vector<string> words = split(initmsg, ' ');
        // for(auto elem: words) cout << elem << "-" ;
        // cout << "\n";
        p.side = words.at(1);
        p.number = words.at(2);
        p.playMode = words.at(3);
    }

    return p;
}


/**
 * @brief processCommand . It processes received message and creates command.
 * @param msg . Message received from the server.
 * @return command to send to the server
 */
Player processCommand(Player const & player){

    Player p{player};

    // parse messages
    p = parseInitMsg(p);
    // ... more parse functions;

    // message already processed. Clean.
    p.msg.clear();

    // generate command based on player info
    p = generateCommand(p);


    return p;
}

int main()
{

    Player player;
    player.teamName="TeamAlberto";
    player.number="";
    player.side="";
    player.playMode="";
    player.commandToSend="(init TeamAlberto)";
    player.msg="";


    int serverPort{6000};
    QHostAddress serverAddres{"127.0.0.1"};
    QUdpSocket socket;
    string command{"(init Alberto)"};
    socket.writeDatagram(player.commandToSend.c_str(), player.commandToSend.length(), serverAddres, serverPort);

    QHostAddress host;
    u_int16_t port;

    while(true){
        while(socket.hasPendingDatagrams())
        {
            QByteArray datagram;
            datagram.resize(socket.pendingDatagramSize());
            socket.readDatagram(datagram.data(),datagram.size(),&host,&port);
            serverPort=port;
            player.msg = datagram.toStdString();
            player = processCommand(player);
            if(player.commandToSend.size()>0)
                socket.writeDatagram(player.commandToSend.c_str(), player.commandToSend.length(), serverAddres, serverPort);
        }
        QThread::msleep(50); // wait 100 miliseconds (to avoid overclocking)
    }
}
