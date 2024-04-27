/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpicoli- <lpicoli-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 10:41:57 by ialves-m          #+#    #+#             */
/*   Updated: 2024/04/27 20:35:48 by lpicoli-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ircserv.hpp"

Channel::Channel(std::string name, bool isPrivate)
{
	this->_name = name;
	this->_isPrivate = isPrivate;
	this->_isInviteOnly = false;
	this->_restrictedTopic = true;
	this->_modes.push_back('n');
	this->_modes.push_back('t');
	this->_creationTime = time(0);
}

std::string Channel::getCreationTime(void)
{
	time(&this->_creationTime);

	std::ostringstream oss;
	oss << this->_creationTime;
	std::string strTime = oss.str();
	return strTime;
}

int Channel::getNbrUsers(void)
{
	return this->_clients.size();
}

/**
 * @brief Get the users in the channel.
 * 
 * This function returns a reference to the map of users in the channel.
 * The map is of type std::map<std::string, Client>, where the keys are
 * strings representing the usernames and the values are instances of the
 * Client class.
 * 
 * @return std::map<std::string, Client>& A reference to the map of users in the channel.
 */
std::map<std::string, Client>& Channel::getUsers(void)
{
	return this->_clients;
}

std::vector<std::string> &Channel::getOperators(void)
{
	return this->_operators;
}

/**
 * @brief Get the name of the channel.
 *
 * @return The name of the channel.
 */
std::string Channel::getName(void)
{
	return this->_name;
}

/**
 * @brief Get the topic of the channel.
 *
 * @return The topic of the channel.
 */
std::string Channel::getTopic(void)
{
	return this->_topic;
}

/**
 * @brief Get the password of the channel.
 *
 * @return The password of the channel.
 */
std::string Channel::getPassword(void)
{
	return this->_password;
}

/**
 * @brief Get the mode status of the channel's topic.
 *
 * @return True if the topic can be edited, false if topic is locked.
 */
bool Channel::getInvisibility(void)
{
    return this->_isInviteOnly;
}

/**
 * @brief Get the mode status of the channel's topic.
 *
 * @return True if the topic is locked, false can be edited.
 */
bool Channel::getRestrictedTopic(void)
{
	return this->_restrictedTopic;
}

/**
 * @brief Get the mode status of private access to the channel.
 *
 * @return True if channel is in private access mode, false if channel is public.
 */
bool Channel::getModeRestrictedAccess(void)
{
	return this->_isPrivate;
}

/**
 * @brief Get the user limit of the channel.
 * 
 * @return int The user limit of the channel.
 */
int Channel::getUserLimit(void)
{
	return this->_userLimit;
}

std::vector<char> Channel::getModes(void)
{
	return this->_modes;
}

bool Channel::isNewMode(char mode)
{
	std::vector<char> modes = this->getModes();
	for (size_t i = 0; i < modes.size(); i++)
	{
		if (modes[i] == mode)
			return false;
	}
	return true;
}

std::vector<std::string> &Channel::getInvitedUsers(void)
{
	return this->_invited;
}


/**
 * @brief Set the name of the channel.
 *
 * @param name The name to set for the channel.
 */
void Channel::setName(std::string name)
{
	this->_name = name;
}

/**
 * @brief Set the topic of the channel.
 *
 * @param topic The topic to set for the channel.
 */
void Channel::setTopic(std::string topic)
{
	this->_topic = topic;
}

/**
 * @brief Set the mode status of the channel's topic.
 *
 * @param mode Set True to allow topic editing, False to block topic editing.
 */
void Channel::setInvisibility(bool mode)
{
	this->_isInviteOnly = mode;
}

/**
 * @brief Set the mode status of private access to the channel.
 *
 * @param mode The mode status to set for private access.
 * Set True to active private access only, false to active public access.
 */
void Channel::setModeRestrictedAccess(bool mode)
{
	this->_isPrivate = mode;
}

/**
 * Checks if a bot exists in the channel.
 * 
 * @return true if a bot exists in the channel, false otherwise.
 */
bool Channel::botExists()
{
	std::map<std::string, Client>::iterator it = this->_clients.begin();
	while (it != this->_clients.end())
	{
		if (it->second.getRealName() == "Bot")
			return true;
		++it;
	}
	return false;
}

/**
 * @brief Adds a new user to the channel.
 * 
 * This function inserts a new user into the channel's list of clients.
 * The user is inserted using their nickname as the key and the client object as the value.
 * 
 * @param client The client object representing the new user.
 */
void	Channel::setNewUser(Client client)
{
	this->_clients.insert(std::make_pair(client.getNick(), client));
}

void Channel::setNewMode(char mode)
{
	this->_modes.push_back(mode);
}

/**
 * @brief Sets the user limit for the channel.
 * 
 * This function sets the maximum number of users allowed in the channel.
 * 
 * @param limit The user limit for the channel.
 */
void Channel::setUserLimit(int limit)
{
	this->_userLimit = limit;
}

/**
 * @brief Sets the password for the channel.
 * 
 * This function sets the password for the channel.
 * 
 * @param password The password to set for the channel.
 */
void Channel::setPassword(std::string password)
{
	this->_password = password;
}

/**
 * @brief Set the restricted topic mode for the channel.
 * 
 * @param mode The mode to set for the restricted topic.
 */
void Channel::setRestrictedTopic(bool mode)
{
	this->_restrictedTopic = mode;
}

void Channel::setBot(Client *bot)
{
	this->_bot = bot;
}

Client *Channel::getBot(void)
{
	return this->_bot;
}

/**
 * @brief Adds an operator to the channel's operator list.
 * 
 * This function adds the specified nickname to the channel's operator list, 
 * if it is not already present. If the nickname is already in the list, 
 * a message is printed to the console indicating that the operator is already in the list.
 * 
 * @param nickname The nickname of the operator to be added.
 */
void	Channel::AddOperator(const std::string& nickname)
{
	std::vector<std::string>::iterator it;
	bool Op_flag = false;

	for (it = this->_operators.begin(); it != this->_operators.end(); ++it)
	{
		if (*it == nickname)
		{
			std::cout << "Operator already in this channel list" << std::endl;
			Op_flag = true;
		}
	}
	if (!Op_flag)
		this->_operators.push_back("@" + nickname);

	if(_isInviteOnly)
		this->AddInvited(nickname); //adiciona o operador na lista de convidados do canal
}

void	Channel::AddInvited(const std::string& nickname)
{
	std::vector<std::string>::iterator it;

	for (it = this->_invited.begin(); it != this->_invited.end(); ++it)
	{
		if (*it == nickname)
		{
			std::cout << "Operator already in this channel list" << std::endl;
			return ;
		}
	}
	this->_invited.push_back(nickname);
}

/**
 * @brief Removes an operator from the channel.
 * 
 * This function removes the specified nickname from the list of operators in the channel.
 * 
 * @param nickname The nickname of the operator to be removed.
 */
void	Channel::RemoveOperator(std::string nickname)
{
	std::vector<std::string>::iterator it = this->_operators.begin();
	while (it != this->_operators.end())
	{
		if (*it == "@" + nickname)
		{
			it = this->_operators.erase(it);
			return;
		}
		else
			++it;
	}
	if(_isInviteOnly)
		this->RemoveInvited(nickname);
}

void	Channel::RemoveInvited(std::string nickname)
{
	std::vector<std::string>::iterator it = this->_invited.begin();
	while (it != this->_invited.end())
	{
		if (*it == nickname)
		{
			it = this->_invited.erase(it);
			return;
		}
		else
			++it;
	}
}

void Channel::deleteMode(char mode)
{
	for(size_t i = 0; i < _modes.size(); i++)
	{
		if (_modes[i] == mode)
        {
            _modes.erase(_modes.begin() + i);
            i--;
        }
	}
}
