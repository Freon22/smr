<?php
echo $TargetPlayer->getDisplayName(); ?> has been <span class="red">DESTROYED</span>, losing <span class="exp"><?php echo number_format($KillResults['DeadExp'])?></span> experience.<br /><?php
if(isset($ShootingPlayer)) {
	echo $ShootingPlayer->getDisplayName(); ?> salvages <span class="creds"><?php echo number_format($KillResults['KillerCredits']); ?></span> credits from the wreckage and gains <span class="exp"><?php echo number_format($KillResults['KillerExp']); ?></span> experience.<br /><?php
} ?>