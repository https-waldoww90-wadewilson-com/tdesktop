/*
This file is part of Telegram Desktop,
the official desktop version of Telegram messaging app, see https://telegram.org

Telegram Desktop is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

It is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

In addition, as a special exception, the copyright holders give permission
to link the code of portions of this program with the OpenSSL library.

Full license: https://github.com/telegramdesktop/tdesktop/blob/master/LICENSE
Copyright (c) 2014-2017 John Preston, https://desktop.telegram.org
*/
#pragma once

namespace Window {

enum class GifPauseReason {
	Any = 0,
	InlineResults = (1 << 0),
	SavedGifs = (1 << 1),
	Layer = (1 << 2),
	MediaPreview = (1 << 3),
};
Q_DECLARE_FLAGS(GifPauseReasons, GifPauseReason);
Q_DECLARE_OPERATORS_FOR_FLAGS(GifPauseReasons);

class MainWindow;

class Controller {
public:
	Controller(gsl::not_null<MainWindow*> window) : _window(window) {
	}

	gsl::not_null<MainWindow*> window() const {
		return _window;
	}

	// This is needed for History TopBar updating when searchInPeer
	// is changed in the DialogsWidget of the current window.
	base::Observable<PeerData*> &searchInPeerChanged() {
		return _searchInPeerChanged;
	}

	// This is needed while we have one HistoryWidget and one TopBarWidget
	// for all histories we show in a window. Once each history is shown
	// in its own HistoryWidget with its own TopBarWidget this can be removed.
	base::Observable<PeerData*> &historyPeerChanged() {
		return _historyPeerChanged;
	}

	void enableGifPauseReason(GifPauseReason reason);
	void disableGifPauseReason(GifPauseReason reason);
	base::Observable<void> &gifPauseLevelChanged() {
		return _gifPauseLevelChanged;
	}
	bool isGifPausedAtLeastFor(GifPauseReason reason) const;

private:
	gsl::not_null<MainWindow*> _window;

	base::Observable<PeerData*> _searchInPeerChanged;
	base::Observable<PeerData*> _historyPeerChanged;

	GifPauseReasons _gifPauseReasons = { 0 };
	base::Observable<void> _gifPauseLevelChanged;

};

} // namespace Window
