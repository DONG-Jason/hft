#ifndef SENDER_H_
#define SENDER_H_

#include <zmq.hpp>
#include <unistd.h>
#include <string>
#include <memory>
#include <mutex>
#include "struct/exchange_info.h"
#include "struct/market_snapshot.h"
#include "util/common_tools.h"
#include "define.h"
#include "struct/order.h"
#include "struct/command.h"

using namespace std;

class Sender {
 public:
  explicit Sender(const std::string& name, const std::string & bs_mode = "bind", const std::string & zmq_mode = "ipc", const std::string& file_name = "");

  ~Sender();
  inline void Bind(const std::string & address);

  template <typename T>
    inline void Send(const T & t) {
      sock.get()->send(&t, sizeof(T));
      if (f.get()) {
        std::lock_guard<std::mutex> lck(mtx);  // for mutli-thread backtest file writting
        f.get()->write((char*)&t, sizeof(T));
        f.get()->flush();
      }
    }

 private:
  unique_ptr<zmq::context_t> con;
  unique_ptr<zmq::socket_t> sock;
  std::mutex mtx;
  unique_ptr<std::ofstream> f;
};

#endif // SENDER_H_
