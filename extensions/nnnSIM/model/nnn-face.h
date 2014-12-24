/* -*- Mode:C++; c-file-style:"gnu" -*- */
/*
 * Copyright 2014 Waseda University, Sato Laboratory
 *   Author: Zhu Li <phillipszhuli1990@gmail.com>
 *           Jairo Eduardo Lopez <jairo@ruri.waseda.jp>
 *
 *  nnn-face.h is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  nnn-face.h is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero Public License for more details.
 *
 *  You should have received a copy of the GNU Affero Public License
 *  along with nnn-face.h.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 *	\file
 *	\author		Zhu Li, Jairo Eduardo Lopez
 *	\copyright	Waseda University, Sato Laboratory
 *	\date		2014
 *	\brief		Interface abstraction for interfaces used by nnn layer
 *	\details	[detailed description]
 */

/*
 *  Doxygen template for functions:
 *  \function (this can be omitted if the comment block is placed immediately before the declaration
 *  \brief		[brief description]
 *  \param	[parameter name] [description]
 *  \return [description of the return value]
 */

#ifndef NNN_Face_H
#define NNN_Face_H

#include <ostream>
#include <algorithm>
#include <ns3-dev/ns3/ptr.h>
#include <ns3-dev/ns3/object.h>
#include <ns3-dev/ns3/nstime.h>
#include <ns3-dev/ns3/type-id.h>
#include <ns3-dev/ns3/traced-callback.h>

namespace ns3 {

class Packet;
class Node;

namespace nnn {

class NULLp;
class SO;
class DO;
class EN;
class AEN;
class REN;
class DEN;
class INF;


/**
 * \class 	Face
 * \brief 	Virtual class defining NNN face
 *
 * This class defines basic functionality of NNN face. Face is core
 * component responsible for actual delivery of all NNN packets to and
 * from NDN stack
 *
 */
class Face :
		public Object
{
public:
	static TypeId

	GetTypeId ();


	typedef Callback<void, Ptr<Face>, Ptr<NULLp> > NULLpHandler;
	typedef Callback<void, Ptr<Face>, Ptr<SO> > SOHandler;
	typedef Callback<void, Ptr<Face>, Ptr<DO> > DOHandler;
	typedef Callback<void, Ptr<Face>, Ptr<EN> > ENHandler;
	typedef Callback<void, Ptr<Face>, Ptr<AEN> > AENHandler;
	typedef Callback<void, Ptr<Face>, Ptr<REN> > RENHandler;
	typedef Callback<void, Ptr<Face>, Ptr<DEN> > DENHandler;
	typedef Callback<void, Ptr<Face>, Ptr<INF> > INFHandler;

	/// Default constructor
	Face (Ptr<Node> node);
	virtual ~Face();

	/// Get node to which this face is associated
	Ptr<Node>
	GetNode () const;

	////////////////////////////////////////////////////////////////////

	/**
	 * \brief Register callback to call when new packet arrives on the Face
	 *
	 * This method should call protocol-dependent registration function
	 */
	virtual void
	RegisterProtocolHandlers (const NULLpHandler &NULLpHandler, const SOHandler &SOHandler,
			const DOHandler &DOHandler, const ENHandler &ENHandler,
			const AENHandler &AENHandler, const RENHandler &RENHandler,
			const DENHandler &DENHandler, const INFHandler &INFHandler);

	/**
	 * \brief Un-Register callback to call when new packet arrives on the Face
	 *
	 * This method should call protocol-dependent registration function
	 */
	virtual void
	UnRegisterProtocolHandlers ();

/********** Send *********/

	/**
	 * \brief	Sends out nnn NULL packet through the face
	 * \param 	n_o Smart pointer to NULLp class variable
	 * \return 	TRUE if nnn NULL packet is considered to be send out (enqueued)
	 */
	virtual bool
	SendNULLp (Ptr<const NULLp> n_o);

	/**
	 * \brief	Sends out SO packet through the face
	 * \param 	so_o Smart pointer to SO class variable
	 * \return 	TRUE if SO is considered to be send out (enqueued)
	 */
	virtual bool
	SendSO (Ptr<const SO> so_o);

	/**
	 * \brief	Sends out DO packet through the face
	 * \param	do_o Smart pointer to DO class variable
	 * \return	TRUE if DO packet is considered to be send out (enqueued)
	 */
	virtual bool
	SendDO (Ptr<const DO> do_o);

	/**
	 * \brief	Sends out EN packet through the face
	 * \param	en_o Smart pointer to EN class variable
	 * \return	TRUE if DO packet is considered to be send out (enqueued)
	 */
	virtual bool
	SendEN (Ptr<const EN> en_o);

	/**
	 * \brief	Sends out AEN packet through the face
	 * \param	aen_o Smart pointer to AEN class variable
	 * \return	TRUE if AEN packet is considered to be send out (enqueued)
	 */
	virtual bool
	SendAEN (Ptr<const AEN> aen_o);

	/**
	 * \brief	Sends out REN packet through the face
	 * \param	ren_o Smart pointer to AEN class variable
	 * \return	TRUE if REN packet is considered to be send out (enqueued)
	 */
	virtual bool
	SendREN (Ptr<const REN> ren_o);

	/**
	 * \brief	Sends out DEN packet through the face
	 * \param	den_o Smart pointer to AEN class variable
	 * \return	TRUE if DEN packet is considered to be send out (enqueued)
	 */
	virtual bool
	SendDEN (Ptr<const DEN> den_o);

	/**
	 * \brief	Sends out INF packet through the face
	 * \param	inf_o Smart pointer to AEN class variable
	 * \return	TRUE if INF packet is considered to be send out (enqueued)
	 */
	virtual bool
	SendINF (Ptr<const INF> inf_o);

/********* Receive ********/

	/**
	 * \brief	Receives nnn NULL packet from application or another node and forwards it up to the NDN stack
	 * \param	n_i
	 * \return	TRUE if the packet was received and placed in the stack
	 * By default it is called from inside Receive method, but can be used directly, if appropriate
	 */
	virtual bool
	ReceiveNULLp (Ptr<NULLp> n_i);

	/**
	 * \brief	Receives SO packet from application or another node and forwards it up to the NDN stack
	 * \param	so_i
	 * \return	TRUE if the packet was received and placed in the stack
	 */
	virtual bool
	ReceiveSO (Ptr<SO> so_i);

	/**
	 * \brief	Receives DO packet from application or another node and forwards it up to the NDN stack
	 * \param	do_i
	 * \return	TRUE if the packet was received and placed in the stack
	 */
	virtual bool
	ReceiveDO (Ptr<DO>  do_i);

	/**
	 * \brief	Receives EN packet from application or another node and forwards it up to the NDN stack
	 * \param	en_i
	 * \return	TRUE if the packet was received and placed in the stack
	 */
	virtual bool
	ReceiveEN (Ptr<EN> en_i);

	/**
	 * \brief	Receives AEN packet from application or another node and forwards it up to the NDN stack
	 * \param	aen_i
	 * \return	TRUE if the packet was received and placed in the stack
	 */
	virtual bool
	ReceiveAEN (Ptr<AEN> aen_i);

	/**
	 * \brief	Receives REN packet from application or another node and forwards it up to the NDN stack
	 * \param	ren_i
	 * \return	TRUE if the packet was received and placed in the stack
	 */
	virtual bool
	ReceiveREN (Ptr<REN> ren_i);

	/**
	 * \brief	Receives DEN packet from application or another node and forwards it up to the NDN stack
	 * \param	den_i
	 * \return	TRUE if the packet was received and placed in the stack
	 */
	virtual bool
	ReceiveDEN (Ptr<DEN> den_i);

	/**
	 * \brief	Receives INF packet from application or another node and forwards it up to the NDN stack
	 * \param	inf_i
	 * \return	TRUE if the packet was received and placed in the stack
	 */
	virtual bool
	ReceiveINF (Ptr<INF> inf_i);

	////////////////////////////////////////////////////////////////////

	/**
	 * \brief Assign routing/forwarding metric with Face
	 *
	 * \param metric configured routing metric (cost) of this Face
	 */
	virtual void
	SetMetric (uint16_t metric);

	/**
	 * \brief Get routing/forwarding metric assigned to the Face
	 *
	 * \returns configured routing/forwarding metric (cost) of this Face
	 */
	virtual uint16_t
	GetMetric (void) const;

	/**
	 * These are Face states and may be distinct from actual lower-layer
	 * device states, such as found in real implementations (where the
	 * device may be down but ndn Face state is still up).
	 */

	/**
	 * \brief Enable or disable this Face
	 */
	inline void
	SetUp (bool up = true);

	/**
	 * \brief Returns true if this Face is enabled, false otherwise.
	 */
	inline bool
	IsUp () const;

	/**
	 * @brief Get Face flags
	 *
	 * Face flags may indicate various properties of the Face.  For example, if it is facing Link Layer,
	 * than the returned flags have Face::NETDEVICE bit set.
	 *
	 * @see ndn::Face::Flags for the list of currently defined Face flags --- NEED MODIFY
	 */
	inline uint32_t
	GetFlags () const;

	/**
	 * @brief List of currently defined Face flags
	 */
	enum Flags
	{
		POA = 0,
		APPLICATION = 1 ///< @brief A netDevice Face, temporarily
	};

	/**
	 * @brief Print information about the Face into the stream
	 * @param os stream to write information to
	 */
	virtual std::ostream&
	Print (std::ostream &os) const;

	/**
	 * \brief Set Face Id
	 *
	 * Id is purely informative and should not be used for any other purpose
	 *
	 * \param id id to set
	 */
	inline void
	SetId (uint32_t id);

	/**
	 * \brief Get Face Id
	 *
	 * Id is purely informative and should not be used for any other purpose
	 *
	 * \returns id id to set
	 */
	inline uint32_t
	GetId () const;

	/**
	 * \brief Compare two NN_Faces. Only two NN_Faces on the same node could be compared.
	 *
	 * Internal index is used for comparison.
	 */
	bool
	operator== (const Face &face) const;

	/**
	 * \brief Compare two NN_Faces. Only two NN_Faces on the same node could be compared.
	 *
	 * Internal index is used for comparison.
	 */
	inline bool
	operator!= (const Face &face) const;

	/**
	 * \brief Compare two NN_Faces. Only two NN_Faces on the same node could be compared.
	 *
	 * Internal index is used for comparison.
	 */
	bool
	operator< (const Face &face) const;

protected:
	/**
	 * @brief Send packet down to the stack (towards app or network)
	 */
	virtual bool
	Send (Ptr<Packet> packet);

	/**
	 * @brief Send packet up to the stack (towards forwarding strategy)
	 */
	virtual bool
	Receive (Ptr<const Packet> p);

	/**
	 * @brief Set Face flags
	 */
	void
	SetFlags (uint32_t flags);

private:
	Face (const Face &); ///< \brief Disabled copy constructor
	Face& operator= (const Face &); ///< \brief Disabled copy operator

protected:
	Ptr<Node> m_node; ///< \brief Smart pointer to Node

private:
	NULLpHandler m_upstreamNULLpHandler;
	SOHandler m_upstreamSOHandler;
	DOHandler m_upstreamDOHandler;
	ENHandler m_upstreamENHandler;
	AENHandler m_upstreamAENHandler;
	RENHandler m_upstreamRENHandler;
	DENHandler m_upstreamDENHandler;
	INFHandler m_upstreamINFHandler;
	bool m_ifup;
	uint32_t m_id; ///< \var id of the interNN_Face in NNN stack (per-node uniqueness)
	uint16_t m_metric; ///< \brief metric of the Face
	uint32_t m_flags; ///< @brief NN_Faces flags (e.g., APPLICATION)

}; //Class ends here

std::ostream&
operator<< (std::ostream& os, const Face &face);

inline bool
Face::IsUp (void) const
{
	return m_ifup;
}

inline void
Face::SetUp (bool up/* = true*/)
{
	m_ifup = up;
}

inline uint32_t
Face::GetFlags () const
{
	return m_flags;
}

inline bool
operator < (const Ptr<Face> &lhs, const Ptr<Face> &rhs)
{
	return *lhs < *rhs;
}

void
Face::SetId (uint32_t id)
{
	m_id = id;
}

uint32_t
Face::GetId () const
{
	return m_id;
}

inline bool
Face::operator!= (const Face &face) const
{
	return !(*this == face);
}

} // namespace nnn
} // namespace ns3

#endif // NN_Face_H
