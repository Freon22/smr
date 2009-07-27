<?php
function doBreakingNewsAssign($gameID,&$template)
{
	$db = new SmrMySqlDatabase();
	$db->query('DELETE FROM news WHERE time < '.(TIME - 86400).' AND type = \'breaking\'');
	$db->query('SELECT * FROM news WHERE game_id = '.$gameID.' AND type = \'breaking\' ORDER BY time DESC LIMIT 1');
	if ($db->nextRecord())
	{
		$template->assign('BreakingNews',array('Time' => $db->getField('time'), 'Message' => $db->getField('news_message')));
	}
}
function doLottoNewsAssign($gameID,&$template)
{
	require_once(get_file_loc('bar.functions.inc'));
	checkForLottoWinner($gameID);
	$db = new SmrMySqlDatabase();
	$db->query('SELECT * FROM news WHERE game_id = '.$gameID.' AND type = \'lotto\' ORDER BY time DESC');
	while ($db->nextRecord())
	{
		 $template->assign('LottoNews',array('Time' => $db->getField('time'), 'Message' => $db->getField('news_message')));
	}
}

?>