#include "json.hpp"
#include "json_valid.hpp"
#include "json_srl.hpp"

int main(int argc, char **argv)
{
    // TEST
    // Json::jsonArr arr = {
    //     Json::jsonObj({
    //         { "a", Json(1) },
    //         { "a", Json(1) }
    //     }),
    //     Json::jsonObj({
    //         { "b", Json(2) }
    //     })
    // };
    // Json j =  Json::jsonArr({
    //     Json::jsonObj({
    //         { "a", Json(1) },
    //         { "a", Json(1) }
    //     }),
    //     Json::jsonObj({
    //         { "b", Json(2) }
    //     })
    // });
   // JsonSrl::load_json(argv[1]);

    try
    {
        if (argc == 2)
        {
            Json j = JsonSrl::load_json(argv[1]);
            j.print(0);
            return 0;
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
