#include <iostream>
#include <fstream>
#include <vector>
//#include <string>
//#include <cstdlib>
#include <sstream>

typedef struct {
    const char* cameras_names;
    const char* windows_position;
    const char* camera_feedso;
} configuracao;

int main() {
    // Leitura do arquivo config.cfg
    std::ifstream arquivoConfiguracao("conf.d/conf.cfg");

    if (!arquivoConfiguracao.is_open()) {
        std::cerr << "Erro: Não foi possível abrir o arquivo de configuração 'conf.cfg'" << std::endl;
        return 1;
    }

    // Declaração de variáveis para armazenar configurações
    std::string cameraA, cameraB;
    int16_t x, y, deltaX, deltaY;
    std::string streamCameraA;

    arquivoConfiguracao >> cameraA >> cameraB;
    arquivoConfiguracao >> x >> y >> deltaX >> deltaY;
    arquivoConfiguracao >> streamCameraA;

    std::stringstream prepararComando;

    prepararComando << "vlc " <<
        "'" << streamCameraA << "'";
        /*" --screen-left=" << x <<
        " --screen-top=" << y <<
        " --screen-width=" << deltaX <<
        " --screen-height=" << deltaY <<
        " '" << streamCameraA << "'";
        */
    
    std::string comando;
    comando = prepararComando.str();

    std::cout << comando << std::endl;

    // Executa o comando para iniciar o stream
    int result = system(comando.c_str());
    
    /*
    if (result != 0) {
        std::cerr << "Erro ao executar o VLC" << std::endl;
        return 1;
    }
    */
}
