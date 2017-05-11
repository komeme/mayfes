var sample_play_sound = new Audio("sample.mp3");

function playSound()
{
    sample_play_sound.play();
}

function stopSound()
{
    sample_play_sound.pause();
    sample_play_sound.currentTime = 0;
}
