/* PPTP constants and structs */
#ifndef _CONNTRACK_PPTP_H
#define _CONNTRACK_PPTP_H

/* state of the control session */
enum pptp_ctrlsess_state {
	PPTP_SESSION_NONE,			/* no session present */
	PPTP_SESSION_ERROR,			/* some session error */
	PPTP_SESSION_STOPREQ,			/* stop_sess request seen */
	PPTP_SESSION_REQUESTED,			/* start_sess request seen */
	PPTP_SESSION_CONFIRMED,			/* session established */
};

/* state of the call inside the control session */
enum pptp_ctrlcall_state {
	PPTP_CALL_NONE,
	PPTP_CALL_ERROR,
	PPTP_CALL_OUT_REQ,
	PPTP_CALL_OUT_CONF,
	PPTP_CALL_IN_REQ,
	PPTP_CALL_IN_REP,
	PPTP_CALL_IN_CONF,
	PPTP_CALL_CLEAR_REQ,
};


/* conntrack private data */
struct ip_ct_pptp_master {
	enum pptp_ctrlsess_state sstate;	/* session state */

	/* everything below is going to be per-expectation in newnat,
	 * since there could be more than one call within one session */
	enum pptp_ctrlcall_state cstate;	/* call state */
	__be16 pac_call_id;			/* call id of PAC, host byte order */
	__be16 pns_call_id;			/* call id of PNS, host byte order */

	/* in pre-2.6.11 this used to be per-expect. Now it is per-conntrack
	 * and therefore imposes a fixed limit on the number of maps */
	struct ip_ct_gre_keymap *keymap_orig, *keymap_reply;
};

/* conntrack_expect private member */
struct ip_ct_pptp_expect {
	enum pptp_ctrlcall_state cstate; 	/* call state */
	__be16 pac_call_id;			/* call id of PAC */
	__be16 pns_call_id;			/* call id of PNS */
};


#endif /* _CONNTRACK_PPTP_H */
