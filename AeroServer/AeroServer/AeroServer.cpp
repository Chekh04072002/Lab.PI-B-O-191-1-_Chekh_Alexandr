#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

int PORT = 30780;

int TICKRATE = 64;
float updateInterval = 1000 / TICKRATE;

float ballSpeed = 400;

int WIDTH = 800;
int HEIGHT = 500;

int padSize = 30;
int ballSize = 5;

int randomRange(int min, int max) {
    return min + (rand() % static_cast<int>(max - min + 1));
}

float distance(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

int main() {
    srand(time(0));

    vector<TcpSocket*> clientSockets;
    TcpListener listener;
    Clock mainClock;

    bool gameInProgress = false;

    bool player1W = false;
    bool player1S = false;
    bool player1D = false;
    bool player1A = false;
    bool player2W = false;
    bool player2S = false;
    bool player2D = false;
    bool player2A = false;

    float pad1x = 100, pad1y = HEIGHT / 2;
    float pad2x = WIDTH - 100, pad2y = HEIGHT / 2;

    float ballx = WIDTH / 2;
    float bally = HEIGHT / 2;
    float ballvx = 0;
    float ballvy = 0;

    int score1 = 0;
    int score2 = 0;

    if (listener.listen(PORT) != Socket::Status::Done) {
        cout << "Cannot listen on port " << PORT << endl;

        return 0;
    }

    cout << "Server listening at " << PORT << endl;

    listener.setBlocking(false);

    bool updateClients = false;

    while (true) {
        TcpSocket* client = new TcpSocket;
        client->setBlocking(false);

        Time deltaTime = mainClock.getElapsedTime();
        if (deltaTime.asMilliseconds() >= updateInterval) {
            mainClock.restart();
            updateClients = true;
        }

        if (listener.accept(*client) == Socket::Status::Done) {
            cout << "Client " << client->getRemoteAddress() << " connected" << endl;

            if (gameInProgress) {
                Packet packet;
                packet << "Server full";
                client->send(packet);
                client->disconnect();

                cout << "Client " << client->getRemoteAddress() << " disconnected due to server being full" << endl;
            } else {
                clientSockets.push_back(client);
            }
        } else {
            delete client;
        }

        for (int i = 0; i < clientSockets.size(); i++) {
            Packet packet;
            TcpSocket* currentClientSocket = clientSockets.at(i);
            Socket::Status status = currentClientSocket->receive(packet);

            if (status == Socket::Status::Disconnected) {
                clientSockets.erase(clientSockets.begin() + i);

                cout << "Client " << currentClientSocket->getRemoteAddress() << " disconnected" << endl;

                if (gameInProgress) {
                    gameInProgress = false;

                    cout << "Game ended due to player disconnect. Waiting for players..." << endl;
                }
            } else if (status == Socket::Done) {
                string type;
                packet >> type;
                if (gameInProgress && type == "Press") {
                    string key;
                    packet >> key;

                    if (key == "w") {
                        if (i == 0) player1W = true;
                        else player2W = true;
                    } else if (key == "s") {
                        if (i == 0) player1S = true;
                        else player2S = true;
                    } else if (key == "d") {
                        if (i == 0) player1D = true;
                        else player2D = true;
                    } else if (key == "a") {
                        if (i == 0) player1A = true;
                        else player2A = true;
                    }
                } else if (gameInProgress && type == "Release") {
                    string key;
                    packet >> key;

                    if (key == "w") {
                        if (i == 0) player1W = false;
                        else player2W = false;
                    } else if (key == "s") {
                        if (i == 0) player1S = false;
                        else player2S = false;
                    } else if (key == "d") {
                        if (i == 0) player1D = false;
                        else player2D = false;
                    } else if (key == "a") {
                        if (i == 0) player1A = false;
                        else player2A = false;
                    }
                }
            }
        }

        if (gameInProgress && updateClients) {
            updateClients = false;

            if (player1W) {
                pad1y -= deltaTime.asSeconds() * 500.0f;
                if (pad1y < 10 + padSize) pad1y = 10 + padSize;
            }
            if (player1S) {
                pad1y += deltaTime.asSeconds() * 500.0f;
                if (pad1y > HEIGHT - padSize - 10) pad1y = HEIGHT - padSize - 10;
            }
            if (player1D) {
                pad1x += deltaTime.asSeconds() * 500.0f;
                if (pad1x > WIDTH / 2 - padSize) pad1x = WIDTH / 2 - padSize;
            }
            if (player1A) {
                pad1x -= deltaTime.asSeconds() * 500.0f;
                if (pad1x < 10 + padSize) pad1x = 10 + padSize;
            }
            if (player2W) {
                pad2y -= deltaTime.asSeconds() * 500.0f;
                if (pad2y < 10 + padSize) pad2y = 10 + padSize;
            }
            if (player2S) {
                pad2y += deltaTime.asSeconds() * 500.0f;
                if (pad2y > HEIGHT - padSize - 10) pad2y = HEIGHT - padSize - 10;
            }
            if (player2D) {
                pad2x -= deltaTime.asSeconds() * 500.0f;
                if (pad2x < WIDTH / 2 + padSize) pad2x = WIDTH / 2 + padSize;
            }
            if (player2A) {
                pad2x += deltaTime.asSeconds() * 500.0f;
                if (pad2x > WIDTH - padSize - 10) pad2x = WIDTH - padSize - 10;
            }

            ballx += deltaTime.asSeconds() * ballvx;
            bally += deltaTime.asSeconds() * ballvy;

            if (bally < 10 || bally > HEIGHT - 10) ballvy *= -1;
            if ((ballx < 10 || ballx > WIDTH - 10) && (bally <= HEIGHT * 0.35 || bally >= HEIGHT * 0.65)) ballvx *= -1;

            if (distance(pad1x, pad1y, ballx, bally) <= padSize + ballSize) {
                float nBallvx = ballvx / sqrt(ballvx * ballvx + ballvy * ballvy);
                float nBallvy = ballvy / sqrt(ballvx * ballvx + ballvy * ballvy);

                float dirx = ballx - pad1x;
                float diry = bally - pad1y;

                float nDirx = dirx / sqrt(dirx * dirx + diry * diry);
                float nDiry = diry / sqrt(dirx * dirx + diry * diry);

                float newdirx = nBallvx + nDirx;
                float newdiry = nBallvy + nDiry;

                ballvx = newdirx / sqrt(newdirx * newdirx + newdiry * newdiry) * ballSpeed;
                ballvy = newdiry / sqrt(newdirx * newdirx + newdiry * newdiry) * ballSpeed;
            }

            if (distance(pad2x, pad2y, ballx, bally) <= padSize + ballSize) {
                float nBallvx = ballvx / sqrt(ballvx * ballvx + ballvy * ballvy);
                float nBallvy = ballvy / sqrt(ballvx * ballvx + ballvy * ballvy);

                float dirx = ballx - pad2x;
                float diry = bally - pad2y;

                float nDirx = dirx / sqrt(dirx * dirx + diry * diry);
                float nDiry = diry / sqrt(dirx * dirx + diry * diry);

                float newdirx = nBallvx + nDirx;
                float newdiry = nBallvy + nDiry;

                ballvx = newdirx / sqrt(newdirx * newdirx + newdiry * newdiry) * ballSpeed;
                ballvy = newdiry / sqrt(newdirx * newdirx + newdiry * newdiry) * ballSpeed;
            }

            if ((ballx < 10 || ballx > WIDTH - 10) && bally < HEIGHT * 0.65 && bally > HEIGHT * 0.3) {

                if (ballx > WIDTH - 10) {
                    score1++;
                    Packet p1;
                    p1 << "Score" << true;
                    clientSockets.at(0)->send(p1);

                    Packet p2;
                    p2 << "Score" << false;
                    clientSockets.at(1)->send(p2);
                } else {
                    score2++;
                    Packet p1;
                    p1 << "Score" << false;
                    clientSockets.at(0)->send(p1);

                    Packet p2;
                    p2 << "Score" << true;
                    clientSockets.at(1)->send(p2);
                }

                ballx = WIDTH / 2;
                bally = HEIGHT / 2;
                pad1x = 100;
                pad1y = HEIGHT / 2;
                pad2x = WIDTH - 100;
                pad2y = HEIGHT / 2;

                int angle = randomRange(0, 360);
                ballvx = cos(angle) * (180.0 / 3.141592653589793238463);
                ballvy = sin(angle) * (180.0 / 3.141592653589793238463);

                float nBallvx = ballvx / sqrt(ballvx * ballvx + ballvy * ballvy);
                float nBallvy = ballvy / sqrt(ballvx * ballvx + ballvy * ballvy);

                ballvx = nBallvx * ballSpeed;
                ballvy = nBallvy * ballSpeed;
            }

            Packet b1;
            b1 << "Move ball" << ballx << bally;
            clientSockets.at(0)->send(b1);

            Packet b2;
            b2 << "Move ball" << (WIDTH - ballx) << bally;
            clientSockets.at(1)->send(b2);

            Packet p;
            p << "Move pad1" << pad1x << pad1y;
            clientSockets.at(0)->send(p);

            Packet p3;
            p3 << "Move pad2" << pad2x << pad2y;
            clientSockets.at(0)->send(p3);

            Packet p2;
            p2 << "Move pad1" << (WIDTH - pad2x) << pad2y;
            clientSockets.at(1)->send(p2);

            Packet p1;
            p1 << "Move pad2" << (WIDTH - pad1x) << pad1y;
            clientSockets.at(1)->send(p1);
        }

        if (clientSockets.size() == 2 && !gameInProgress) {
            gameInProgress = true;
            cout << "Enough client to start a game. Starting game..." << endl;

            Packet packet;
            packet << "Game start";

            clientSockets.at(0)->send(packet);
            clientSockets.at(1)->send(packet);

            int angle = randomRange(0, 360);
            ballvx = cos(angle) * (180.0 / 3.141592653589793238463);
            ballvy = sin(angle) * (180.0 / 3.141592653589793238463);

            float nBallvx = ballvx / sqrt(ballvx * ballvx + ballvy * ballvy);
            float nBallvy = ballvy / sqrt(ballvx * ballvx + ballvy * ballvy);

            ballvx = nBallvx * ballSpeed;
            ballvy = nBallvy * ballSpeed;
        }
    }

    return 0;
}