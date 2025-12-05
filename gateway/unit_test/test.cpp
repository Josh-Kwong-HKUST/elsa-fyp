#include "quickfix/config.h"

#include "../src/gatewayApplication.h"
#include "quickfix/FileStore.h"
#include "quickfix/SessionSettings.h"
#include "quickfix/SocketAcceptor.h"

#include <fstream>
#include <iostream>
#include <string>

#include <filesystem>
namespace fs = std::filesystem;

int main(int argc, char **argv)
{
    try
    {
        fs::path configFileName = "example_config_server.cfg";
        fs::path pathToConfig = fs::current_path() / configFileName;

        FIX::SessionSettings settings(pathToConfig);

        Application application;
        FIX::FileStoreFactory storeFactory(settings);
        FIX::ScreenLogFactory logFactory(settings);
        FIX::SocketAcceptor acceptor(application, storeFactory, settings, logFactory);

        acceptor.start();
        while (true)
        {
            // Keep the server running
        }
        acceptor.stop();
        return 0;
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }
}