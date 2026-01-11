#include "AudioPlayer.hpp"

NAMESPACE_BAD_APPLE_BEGIN

namespace IO
{
    AudioPlayer::AudioPlayer()
    {
        // 初始化引擎
        ma_result result = ma_engine_init(nullptr, &m_engine);
        if (result != ma_result::MA_SUCCESS)
        {
            std::cerr << "[Audio] Failed to initialize audio engine, ma_engine_init failed with error code " << result << std::endl;
            return;
        }
        m_initialized = true;
    }

    AudioPlayer::~AudioPlayer()
    {
        if (m_loaded)
        {
            ma_sound_uninit(&m_sound);
        }
        if (m_initialized)
        {
            ma_engine_uninit(&m_engine);
        }
    }

    bool AudioPlayer::load(const std::string& path)
    {
        if (!m_initialized) return false;

        // 如果之前加载过, 先清理
        if (m_loaded)
        {
            ma_sound_uninit(&m_sound);
            m_loaded = false;
        }

        // 加载声音文件
        ma_result result = ma_sound_init_from_file(
            &m_engine,
            path.c_str(),
            0,
            nullptr,
            nullptr,
            &m_sound
            );
        if (result != ma_result::MA_SUCCESS)
        {
            std::cerr << "[Audio] Failed to load sound: " << path << std::endl;
            return false;
        }

        m_loaded = true;
        return true;
    }

    void AudioPlayer::play()
    {
        if (m_loaded)
        {
            ma_sound_start(&m_sound);
        }
    }

    void AudioPlayer::stop()
    {
        if (m_loaded && is_playing())
        {
            ma_sound_stop(&m_sound);
        }
    }

    bool AudioPlayer::is_playing() const
    {
        if (!m_loaded)
            return false;
        return ma_sound_is_playing(&m_sound);
    }

    std::int64_t AudioPlayer::get_time_ms() const
    {
        if (!m_loaded)
            return 0;

        float cursor_seconds = 0.0f;
        ma_result res = ma_sound_get_cursor_in_seconds(&m_sound, &cursor_seconds);
        if (res != ma_result::MA_SUCCESS)
            return 0;

        return std::int64_t(cursor_seconds * 1000.0f);
    }
}

NAMESPACE_BAD_APPLE_END