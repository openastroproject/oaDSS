/*****************************************************************************
 *
 * mainWindow.h -- class declaration
 *
 * Copyright 2024
 *     James Fidell (james@openastroproject.org)
 *
 * License:
 *
 * This file is part of the Open Astro Project.
 *
 * The Open Astro Project is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The Open Astro Project is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the Open Astro Project.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 *****************************************************************************/

#pragma once

#include <unordered_set>
#include <mutex>

template<typename K, typename H>
class concurrent_unordered_set
{
	private:
		std::unordered_set<K,H>	data;
		mutable std::mutex			m;

	public:
		typedef std::unordered_set<K,H>::iterator iterator;
		typedef std::unordered_set<K,H>::const_iterator const_iterator;

														concurrent_unordered_set() = default;
														~concurrent_unordered_set() {};

		[[nodiscard]] bool			empty() const noexcept
		{
			const std::lock_guard<std::mutex> lock( m );
			return data.empty();
		}

		void										clear() noexcept
		{
			const std::lock_guard<std::mutex> lock( m );
			data.clear();
		}

		const_iterator					cend() const noexcept
		{
			const std::lock_guard<std::mutex> lock( m );
			return data.cend();
		}

		const_iterator	find( const K& val )
		{
			const std::lock_guard<std::mutex> lock( m );
			return data.find( val );
		}

		std::pair<iterator, bool> insert( const K& val )
		{
			const std::lock_guard<std::mutex> lock( m );
			return data.insert(val);
		}
};
