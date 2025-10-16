import { useState, useEffect } from 'react'
import './App.css'

interface MarketData {
  symbol: string
  price: number
  change: number
  volume: number
}

function App() {
  const [marketData, setMarketData] = useState<MarketData[]>([
    { symbol: 'AAPL', price: 175.43, change: 2.34, volume: 1234567 },
    { symbol: 'GOOGL', price: 142.65, change: -1.23, volume: 987654 },
    { symbol: 'MSFT', price: 378.91, change: 5.67, volume: 2345678 },
    { symbol: 'AMZN', price: 145.23, change: -0.89, volume: 1567890 },
  ])
  const [isConnected, setIsConnected] = useState(false)

  useEffect(() => {
    // Simulate connection status
    const timer = setTimeout(() => setIsConnected(true), 1000)
    return () => clearTimeout(timer)
  }, [])

  useEffect(() => {
    // Simulate real-time price updates
    if (!isConnected) return

    const interval = setInterval(() => {
      setMarketData(prev => prev.map(stock => ({
        ...stock,
        price: stock.price + (Math.random() - 0.5) * 2,
        change: stock.change + (Math.random() - 0.5) * 0.5,
        volume: stock.volume + Math.floor((Math.random() - 0.5) * 10000)
      })))
    }, 2000)

    return () => clearInterval(interval)
  }, [isConnected])

  return (
    <div className="app">
      <header className="header">
        <h1>ELSA - Market Simulation</h1>
        <div className={`status ${isConnected ? 'connected' : 'disconnected'}`}>
          {isConnected ? '● Connected' : '○ Disconnected'}
        </div>
      </header>

      <main className="main">
        <section className="dashboard">
          <h2>Market Dashboard</h2>
          <div className="market-grid">
            {marketData.map((stock) => (
              <div key={stock.symbol} className="market-card">
                <h3>{stock.symbol}</h3>
                <div className="price">${stock.price.toFixed(2)}</div>
                <div className={`change ${stock.change >= 0 ? 'positive' : 'negative'}`}>
                  {stock.change >= 0 ? '▲' : '▼'} {Math.abs(stock.change).toFixed(2)}%
                </div>
                <div className="volume">Vol: {stock.volume.toLocaleString()}</div>
              </div>
            ))}
          </div>
        </section>

        <section className="info">
          <h2>About</h2>
          <p>
            Market Simulation for Algorithmic Trading - A real-time trading 
            simulation environment for testing and developing trading algorithms.
          </p>
        </section>
      </main>

      <footer className="footer">
        <p>ELSA FYP © 2025 - Market Simulation Platform</p>
      </footer>
    </div>
  )
}

export default App
