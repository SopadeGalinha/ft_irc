/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 17:50:44 by ialves-m          #+#    #+#             */
/*   Updated: 2024/04/24 21:29:45 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CLIENT_
#define _CLIENT_

#include "ircserv.hpp"

/**
 * @brief Represents a client in the IRC server.
 */
class Client {

	protected:
		std::string _nick; 				/* The nickname of the client. */
		std::string _serverPassword; 	/* The password for connecting to the server. */
		std::string _tmpPassword; 		/* Temporary password for authentication. */
		std::string _username; 			/* The username of the client. */
		std::string _realname;			/* The real name of the client. */
		pollfd clientPoll; 				/* The pollfd structure for polling events on the client's socket. */
		

	public:
		/**
		 * @brief Default constructor for the Client class.
		 */
		Client(void);

		virtual ~Client(void);

		/**
		 * @brief Get the real name of the client.
		 * @return The real name of the client.
		 */
		std::string getRealName(void);
		
		/**
		 * @brief Get the nickname of the client.
		 * @return The nickname of the client.
		 */
		std::string getNick(void) const;

		/**
		 * @brief Get the username of the client.
		 * @return The username of the client.
		 */
		std::string getUsername(void) const;

		/**
		 * @brief Get the temporary password of the client.
		 * @return The temporary password of the client.
		 */
		std::string getTmpPassword(void);

		/**
		 * @brief Get the socket file descriptor of the client.
		 * @return The socket file descriptor of the client.
		 */
		int getSocket(void) const;

		/**
		 * @brief Get the pollfd structure for polling events on the client's socket.
		 * @return The pollfd structure for polling events on the client's socket.
		 */
		pollfd getClientPoll(void);

		/**
		 * @brief Set the nickname of the client.
		 * @param nick The nickname to set.
		 */
		void setNick(std::string nick);

		/**
		 * @brief Set the real name of the client.
		 * @param realname The real name to set.
		 */
		void setRealName(std::string realname);

		/**
		 * @brief Set the username of the client.
		 * @param username The username to set.
		 */
		void setUsername(std::string username);

		/**
		 * @brief Set the temporary password of the client.
		 * @param pass The temporary password to set.
		 */
		void setTmpPassword(std::string pass);

		/**
		 * @brief Set a new client object.
		 * @param client The new client object to set.
		 */
		void setNewClient(Client &client);

		/**
		 * @brief Set the socket file descriptor of the client.
		 * @param fd The socket file descriptor to set.
		 */
		void setSocket(int fd);

		/**
		 * @brief Set the file descriptor for polling events on the client's socket.
		 * @param fd The file descriptor to set.
		 */
		void setPoll_fd(int fd);

		/**
		 * @brief Set the events to poll for on the client's socket.
		 */
		void setPoll_events(void);

		/**
		 * @brief Set the events that occurred on the client's socket.
		 */
		void setPoll_revents(void);

		/**
		 * @brief Get the login data of the client.
		 * @param buffer The buffer containing the login data.
		 * @param bytesRead The number of bytes read from the buffer.
		 * @param globalUsers The map of global users.
		 * @param hostname The hostname of the server.
		 */
		void getClientLoginData(std::string message, std::map<std::string, Client> globalUsers, std::string hostname);
		
		virtual void help() {}
};

#endif