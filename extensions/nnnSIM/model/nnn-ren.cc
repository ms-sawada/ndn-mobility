/* -*- Mode: C++; c-file-style: "gnu" -*- */
/*
 * Copyright 2014 Waseda University, Sato Laboratory
 *   Author: Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 *
 *  nnn-do.cc is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-do.cc is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero Public License for more details.
 *
 *  You should have received a copy of the GNU Affero Public License
 *  along with nnn-en.cc.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <ns3-dev/ns3/log.h>
#include <ns3-dev/ns3/unused.h>
#include <ns3-dev/ns3/packet.h>

#include "nnn-ren.h"

NS_LOG_COMPONENT_DEFINE ("nnn.REN");

namespace ns3 {
namespace nnn {

REN::REN ()
 : m_packetid (5)
 , m_ttl      (Seconds (0))
 , m_wire     (0)
{

}

REN::REN (Ptr<NNNAddress> name)
 : m_packetid (5)
 , m_ttl      (Seconds (1))
 , m_name     (name)
 , m_wire     (0)

REN::REN (const NNNAddress &name, Ptr<Packet> payload)
 : m_packetid (5)
 , m_ttl      (Seconds (1))
 , m_name     (Create<NNNAddress> (name))
 , m_wire     (0)


REN::REN (const REN &ren_p)
 : m_packetid (5)
 , m_ttl      (ren_p.m_ttl)
 , m_length   (ren_p.m_length)
 , m_name     (Create<NNNAddress> (ren_p.GetName()))
 , m_wire     (0)
{
	NS_LOG_FUNCTION("REN correct copy constructor");
}

void
REN::SetName (Ptr<NNNAddress> name)
{
	m_name = name;
	m_wire = 0;
}

void
REN::SetName (const NNNAddress &name)
{
	m_name = Create<NNNAddress> (name);
	m_wire = 0;
}


const NNNAddress&
REN::GetName () const
{
	if (m_name == 0) throw RENException ();
	return *m_name;
}


Ptr<const NNNAddress>
REN::GetNamePtr () const
{
	return m_name;
}

void
REN::SetLifetime (Time ttl)
{
	m_ttl = ttl;
	m_wire = 0;
}

Time
REN::GetLifetime () const
{
	return m_ttl;
}

void
REN::Print (std::ostream &os) const
{
	os << "<REN>\n";
	os << "  <TTL>" << GetLifetime () << "</TTL>\n";
	os << "  <Name>" << GetName () << "</Name>\n";
	os << "</REN>";
}

} // namespace nnn
} // namespace ns3