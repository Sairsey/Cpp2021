#include <Windows.h>
#include <string>
#include <vector>
#include <map>

/*! \brief prototype of any unary function
 * \author Vladimir Parusov
 * \version 1.0
 */
using unary_func = double(*)(double);

/*! \brief prototype of any binary function
 * \author Vladimir Parusov
 * \version 1.0
 */
using binary_func = double(*)(double, double);

/*! \brief type which represents table with unary operations
 * \author Vladimir Parusov
 * \version 1.0
 */
using unary_table = std::map<std::string, unary_func>;

/*! \brief type which represents table with binary operations
 * \author Vladimir Parusov
 * \version 1.0
 */
using binary_table = std::map<std::string, binary_func>;

/*! DLL import specific type */
using unary_loader = unary_table & (*)(void);
/*! DLL import specific type */
using binary_loader = binary_table & (*)(void);

/*! \brief class which represents loading of plugins in runtime
 * \author Vladimir Parusov
 * \version 1.0
 */
class plugin_loader
{
    std::vector<HMODULE> to_free; //!< elements we want to free after session will be closed
  public:
    unary_table dll_unary_table; //!< table with unary opeartors loaded from all plugins 
    binary_table dll_binary_table; //!< table with binary opeartors loaded from all plugins

    /*! Constructor from path to directory
     * \param[in] plugins_path - path to plugins directory. Default "plugins/".
     */
    plugin_loader(std::string plugins_path = "plugins/");


    /*! Helper function for loading unary operations from plugin
     * \param[in] lib - DLL handler
     */
     void load_unary(HMODULE lib);
    
    /*! Helper function for loading binary operations from plugin
     * \param[in] lib - DLL handler
     */
    void load_binary(HMODULE lib);

    /*! Destructor */
    ~plugin_loader();
};
