#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <sstream>
#include <vector>
#include <time.h>

#include <tchar.h>

const int n = 10;

std::atomic_int m_number;
std::atomic_int m_nextTicket;
std::atomic_int m_currentTicket[n];

int m_numberOfThreads;
std::mutex m_mutexCount;


void processeONE()
{
    int i = m_numberOfThreads++;

    m_mutexCount.lock();
    std::cout << "Thread " << i << "clocking in" << std::endl;
    m_mutexCount.unlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 500));

    int start = clock();
    double diff = (clock() - start) / (double)(CLOCKS_PER_SEC);

    while (diff <= 60)
    {
        diff = (clock() - start) / (double)(CLOCKS_PER_SEC);

        //Take a ticket
        m_currentTicket[i] = m_number.fetch_add(1);

        m_mutexCount.lock();
        std::cout << "t" << i << "\tturn: " << m_currentTicket[i] << std::endl;
        m_mutexCount.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(1));

        while (m_currentTicket[i] != m_nextTicket)
        {
            continue;
        }

        //critical section
        m_mutexCount.lock();
        std::cout << "t" << i << "\t entering critical section" << std::endl;
        m_mutexCount.unlock();
        std::cout << "player effected processeONE" << std::endl;



        m_nextTicket += 1;
        m_mutexCount.lock();
        std::cout << "t" << i << "\t next ticket = " << m_nextTicket << std::endl;
        m_mutexCount.unlock();

        std::cout << "" << std::endl;
    }
}
void processeTWO()
{
    int i = m_numberOfThreads++;  //Intentional post-increment

    m_mutexCount.lock();
    std::cout << "Thread " << i << " reporting in." << std::endl;
    m_mutexCount.unlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 500));


    int start = clock();
    double diff = (clock() - start) / (double)(CLOCKS_PER_SEC);

    while (diff <= 60)
    {
        //Take a ticket
        m_currentTicket[i] = m_number.fetch_add(1);

        m_mutexCount.lock();
        std::cout << "t" << i << "\tturn: " << m_currentTicket[i] << std::endl;
        m_mutexCount.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(1));

        while (m_currentTicket[i] != m_nextTicket)
        {
            continue;
        }

        //critical section
        m_mutexCount.lock();
        std::cout << "t" << i << "\t entering critical section" << std::endl;
        m_mutexCount.unlock();
        std::cout << "player effected processeTWO" << std::endl;



        m_nextTicket += 1;
        m_mutexCount.lock();
        std::cout << "t" << i << "\t next ticket = " << m_nextTicket << std::endl;
        m_mutexCount.unlock();

        std::cout << "" << std::endl;
    }
}
void processeTHREE()
{
    int i = m_numberOfThreads++;  //Intentional post-increment

    m_mutexCount.lock();
    std::cout << "Thread " << i << " reporting in." << std::endl;
    m_mutexCount.unlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 500));


    int start = clock();
    double diff = (clock() - start) / (double)(CLOCKS_PER_SEC);

    while (diff <= 60)
    {
        //Take a ticket
        m_currentTicket[i] = m_number.fetch_add(1);

        m_mutexCount.lock();
        std::cout << "t" << i << "\tturn: " << m_currentTicket[i] << std::endl;
        m_mutexCount.unlock();

        std::this_thread::sleep_for(std::chrono::seconds(1));

        while (m_currentTicket[i] != m_nextTicket)
        {
            continue;
        }

        //critical section
        m_mutexCount.lock();
        std::cout << "t" << i << "\t entering critical section" << std::endl;
        m_mutexCount.unlock();
        std::cout << "player effected processeTHREE" << std::endl;

        m_nextTicket += 1;
        m_mutexCount.lock();
        std::cout << "t" << i << "\t next ticket = " << m_nextTicket << std::endl;
        m_mutexCount.unlock();

        std::cout << "" << std::endl;
    }
}
void processeFOUR()
{
    int i = m_numberOfThreads++;  //Intentional post-increment

    m_mutexCount.lock();
    std::cout << "Thread " << i << " reporting in." << std::endl;
    m_mutexCount.unlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 500 + 500));

    int start = clock();
    double diff = (clock() - start) / (double)(CLOCKS_PER_SEC);

    while (diff <= 60)
    {
        //Take a ticket
        m_currentTicket[i] = m_number.fetch_add(1);

        m_mutexCount.lock();
        std::cout << "t" << i << "\t turn: " << m_currentTicket[i] << std::endl;
        m_mutexCount.unlock();




        std::this_thread::sleep_for(std::chrono::seconds(1));

        while (m_currentTicket[i] != m_nextTicket)
        {
            continue;
        }

        //critical section
        m_mutexCount.lock();
        std::cout << "t" << i << "\t entering critical section" << std::endl;
        m_mutexCount.unlock();
        std::cout << "player effected processeFOUR" << std::endl;


     
        m_nextTicket += 1;
        m_mutexCount.lock();
        std::cout << "t" << i << "\t next ticket = " << m_nextTicket << std::endl;
        m_mutexCount.unlock();

        std::cout << "" << std::endl;
    }
}




int _tmain(int argc, _TCHAR* argv[])
{
    srand(time(NULL));
    std::string m_player;

    m_numberOfThreads = 0;
    m_number = 1;
    m_nextTicket = 1;
    for (int i = 0; i < n; i++)
    {
        m_currentTicket[i] = 0;
    }

    std::thread t1 = std::thread(processeONE);
    std::thread t2 = std::thread(processeTWO);
    std::thread t3 = std::thread(processeTHREE);
    std::thread t4 = std::thread(processeFOUR);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}