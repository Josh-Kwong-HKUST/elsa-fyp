# ELSA - Market Simulation Frontend

Web-based frontend for the Market Simulation for Algorithmic Trading platform.

## Features

- Real-time market data dashboard
- Live price updates and visualizations
- Trading simulation monitoring
- Responsive design for desktop and mobile

## Technology Stack

- **React 19** - UI framework
- **TypeScript** - Type-safe development
- **Vite** - Fast build tool and dev server
- **CSS3** - Modern styling

## Getting Started

### Prerequisites

- Node.js 18+ and npm 8+

### Installation

```bash
# Install dependencies
npm install
```

### Development

```bash
# Start development server
npm run dev
```

The application will be available at `http://localhost:5173`

### Building for Production

```bash
# Build for production
npm run build

# Preview production build
npm run preview
```

### Linting

```bash
# Run ESLint
npm run lint
```

## Project Structure

```
frontend/
├── src/
│   ├── App.tsx          # Main application component
│   ├── App.css          # Application styles
│   ├── main.tsx         # Entry point
│   └── index.css        # Global styles
├── public/              # Static assets
├── index.html           # HTML template
└── package.json         # Dependencies and scripts
```

## Future Enhancements

- WebSocket integration for real-time data streaming
- Advanced charting with trading indicators
- Algorithm configuration interface
- Performance metrics and analytics
- Historical data visualization
- Trade execution interface
