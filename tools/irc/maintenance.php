<?php

function check_sms_dlr($fp)
{
	// get one dlr per time so we do not spam anyone
	$db = new SmrMySqlDatabase();
	$db->query(
		'SELECT     * ' .
		'FROM       account_sms_dlr ' .
		'LEFT JOIN  account_sms_log USING (message_id) ' .
		'WHERE      announce = 0'
	);
	if ($db->nextRecord()) {
		$message_id = $db->getField('message_id');
		$sender_id = $db->getField('account_id');
		$receiver_id = $db->getField('receiver_id');
		$status = $db->getField('status');
//		$send_time = $db->getField('send_time');
//		$receive_time = $db->getField('receive_time');

		echo_r('Found new DLR... ' . $message_id);

		$sender =& SmrAccount::getAccount($sender_id, true);
		$receiver =& SmrAccount::getAccount($receiver_id, true);

		fputs($fp, 'NOTICE ' . $sender->getIrcNick() . ' :Your text to ' . $receiver->getIrcNick() . ' has been processed. Delivery status: ' . $status . EOL);

		// update announce status
		$db->query('UPDATE account_sms_dlr ' .
		           'SET    announce = 1 ' .
		           'WHERE  message_id = ' . $message_id);
	}

}

function check_planet_builds()
{

}

function check_events($fp)
{
	global $events;

	foreach ($events as $key => $event) {

		if ($event[0] < time()) {
			echo_r('[TIMER] finished. Sending a note to ' . $event[2]);
			fputs($fp, 'NOTICE ' . $event[2] . ' :' . $event[1] . EOL);
			unset($events[$key]);
		}

	}
}

?>