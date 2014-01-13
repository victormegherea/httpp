/*
 * Part of HTTPP.
 *
 * Distributed under the 3-clause BSD licence (See LICENCE.TXT file at the
 * project root).
 *
 * Copyright (c) 2013 Thomas Sanchez.  All rights reserved.
 *
 */

#ifndef _HTTPP_UTILS_THREAD_POOL_HPP_
# define _HTTPP_UTILS_THREAD_POOL_HPP_

# include <cstddef>
# include <vector>
# include <thread>
# include <memory>

# include <boost/asio/io_service.hpp>

namespace HTTPP
{
namespace UTILS
{

class ThreadPool
{
public:
    ThreadPool(size_t nb_thread, boost::asio::io_service& service);
    ~ThreadPool();

    ThreadPool(ThreadPool&& pool);
    ThreadPool& operator=(ThreadPool&&) = delete;

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    template <typename Callable>
    void post(Callable&& callable)
    {
        service_.post(std::forward<Callable>(callable));
    }

    void start();
    void stop();

private:
    boost::asio::io_service& service_;
    bool running_ = false;
    size_t nb_thread_;
    std::unique_ptr<boost::asio::io_service::work> work_;
    std::vector<std::thread> threads_;
};

}
}

#endif // ! HTTPP_UTILS_THREAD_POOL_HPP_
